#include "renderer/Shader.h"

#include <fstream>
#include <sstream>

#include "core/gg.h"
#include "Paths.h"
#include "security/cryptography/crc32.h"
#include "platform/opengl/GLCommon.h"

namespace gg
{
	std::unordered_map<uint, GLuint> Shader::s_ShaderHash;

	Shader::Shader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		_SYS("Processing file: \"" << m_FilePath << "\"");
		// check first if file is already cached
		uint _hash = Crc32::getHash(m_FilePath.c_str(), m_FilePath.size());
		bool _isCached = s_ShaderHash.find(_hash) != s_ShaderHash.end();

		if (_isCached)
		{
			m_ProgramID = s_ShaderHash[_hash];
			return;
		}

		ShaderData _data = parseShader(m_FilePath.c_str());
		if (_data.vsString.empty())
		{
			WARN("No vertex shader found in\n:[" << m_FilePath << "]!");
			return;
		}
		if (_data.fsString.empty())
		{
			WARN("No fragment shader found in\n:[" << m_FilePath << "]!");
			return;
		}

		const char* _vsChar = _data.vsString.c_str();
		const char* _fsChar = _data.fsString.c_str();

		GL(m_ProgramID = glCreateProgram());
		if (m_ProgramID == 0)
		{
			ERROR("Shader program creation failed. Could not find valid memory location in constructor");
			return;
		}
		_SYS("Creating vertex shader");
		if (!attachShader(_vsChar, GL_VERTEX_SHADER))	{ return; }
		_SYS("Creating fragment shader");
		if (!attachShader(_fsChar, GL_FRAGMENT_SHADER)) { return; }
		_SYS("Compiling program");
		if (!compileProgram())							{ return; }

		addAllUniforms();
		m_ShaderID = _hash;
	}

	Shader::~Shader(void)
	{
		GL(glDetachShader(m_ProgramID, GL_VERTEX_SHADER));
		GL(glDetachShader(m_ProgramID, GL_FRAGMENT_SHADER));

		GL(glDeleteProgram(m_ProgramID));
	}

	void Shader::bind(void)
	{
		GL(glUseProgram(m_ProgramID));
	}

	void Shader::addAllUniforms(void)
	{
		int _size = 0;
		int _len = -1;
		int _num = -1;
		GLenum _type = GL_ZERO;
		char _name[256];

		GL(glGetProgramiv(m_ProgramID, GL_ACTIVE_UNIFORMS, &_size));
		FORU(i, 0, (uint)_size)
		{
			GL(glGetActiveUniform(m_ProgramID, i, sizeof(_name) - 1, &_len, &_num, &_type, _name));
			GL(GLint _uniformLoc = glGetUniformLocation(m_ProgramID, _name));

			DataType _dataType = glEnumToDataType(_type);
			if (_dataType == DataType::UNKNOWN)
			{
				ERROR("The uniform [" << _name << "] is of an unknown type! (" << _type << ")");
			}
			else
			{
				_SYS("Adding uniform (" << _uniformLoc << ") <" << dataTypeToString(glEnumToDataType(_type)) << "> " << _name);
				m_Uniforms.push_back(UniformData(_name, glEnumToDataType(_type), _uniformLoc));
			}
		}
	}

	GLvoid Shader::setUniformi(const std::string& key, uint val)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [int][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::INT)
		{
			WARN("Uniform mismatch!\nTrying to set int value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniform1i(_uniformData->loc, val);
	}

	GLvoid Shader::setUniformf(const std::string& key, float val)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [float][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::FLOAT)
		{
			WARN("Uniform mismatch!\nTrying to set float value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniform1f(_uniformData->loc, val);
	}

	GLvoid Shader::setUniform(const std::string& key, Math::Vec3f val)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [vec3][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::VEC3)
		{
			WARN("Uniform mismatch!\nTrying to set vec3 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniform3f(_uniformData->loc, val.x, val.y, val.z);
	}

	void Shader::setUniform(const std::string & key, float x, float y, float z)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [vec3][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::VEC3)
		{
			WARN("Uniform mismatch!\nTrying to set vec3 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniform3f(_uniformData->loc, x, y, z);
	}

	GLvoid Shader::setUniform(const std::string& key, Math::Mat4f val, bool transpose)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [mat4][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::MAT4)
		{
			WARN("Uniform mismatch!\nTrying to set mat4 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniformMatrix4fv(_uniformData->loc, 1, transpose, val.getMatrix());
	}

	GLvoid Shader::setUniform(const std::string& key, float* val, bool transpose)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [mat4][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::MAT4)
		{
			WARN("Uniform mismatch!\nTrying to set mat4 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		glUniformMatrix4fv(_uniformData->loc, 1, transpose, val);
	}

	Shader::DataType Shader::glEnumToDataType(GLenum type)
	{
		switch (type)
		{
		case GL_INT:			return DataType::INT;
		case GL_FLOAT:			return DataType::FLOAT;
		case GL_FLOAT_VEC2_ARB:	return DataType::VEC2;
		case GL_FLOAT_VEC3_ARB:	return DataType::VEC3;
		case GL_FLOAT_VEC4_ARB:	return DataType::VEC4;
		case GL_FLOAT_MAT3:		return DataType::MAT3;
		case GL_FLOAT_MAT4:		return DataType::MAT4;
		case GL_SAMPLER_2D_ARB:	return DataType::SAMPLER2D;
		}
		return DataType::UNKNOWN;
	}

	GLenum Shader::dataTypeToGLEnum(DataType dataType)
	{
		switch (dataType)
		{
		case DataType::INT:			return GL_INT;
		case DataType::FLOAT:		return GL_FLOAT;
		case DataType::VEC2:		return GL_FLOAT_VEC2_ARB;
		case DataType::VEC3:		return GL_FLOAT_VEC3_ARB;
		case DataType::VEC4:		return GL_FLOAT_VEC4_ARB;
		case DataType::MAT3:		return GL_FLOAT_MAT3;
		case DataType::MAT4:		return GL_FLOAT_MAT4;
		case DataType::SAMPLER2D:	return GL_SAMPLER_2D_ARB;
		}
		return 0;
	}

	std::string Shader::dataTypeToString(DataType dataType)
	{
		switch (dataType)
		{
		case DataType::INT:			return "int";
		case DataType::FLOAT:		return "float";
		case DataType::VEC2:		return "vec2";
		case DataType::VEC3:		return "vec3";
		case DataType::VEC4:		return "vec4";
		case DataType::MAT3:		return "mat3";
		case DataType::MAT4:		return "mat4";
		case DataType::SAMPLER2D:	return "sampler2D";
		}
		return "unknown";
	}

	void Shader::logShaderInfo(GLuint shader)
	{
		char _infoLog[512];
		GL(glGetShaderInfoLog(shader, 512, NULL, _infoLog));
		ERROR("[Error] Shader compilation failed!\n" << _infoLog);
	}

	GLvoid Shader::logProgramInfo(GLuint program)
	{
		char _infoLog[512];
		GL(glGetProgramInfoLog(program, 512, NULL, _infoLog));
		ERROR("[Error] Invalid program!\n" << _infoLog);
	}

	const Shader::UniformData* Shader::getUniform(const std::string & key)
	{
		VFOR(it, m_Uniforms)
		{
			if (it->key.compare(key) == 0)
			{
				return &(*it);
			}
		}
		return nullptr;
	}

	Shader::ShaderData Shader::parseShader(const char* file)
	{
		// only used within this function for organization
		struct StreamData
		{
			std::ifstream stream;
			std::string currLine;
		};

		std::vector<StreamData> _streams;
		_streams.push_back({ std::ifstream(file), "" });

		std::stringstream _ss[2];

		ShaderType _type = ShaderType::NONE;

		int _currIndex = (int)_streams.size() - 1;

		while (_currIndex > -1)
		{
			std::string *_line = &_streams[_currIndex].currLine;
			if (!std::getline(_streams[_currIndex].stream, *_line))
			{
				_streams.pop_back();
				_currIndex--;
				continue;
			}
			
			if ((*_line).find("#shader") != std::string::npos)
			{
				if ((*_line).find("vertex") != std::string::npos)
				{
					_type = ShaderType::VERTEX;
				}
				else if ((*_line).find("fragment") != std::string::npos)
				{
					_type = ShaderType::FRAGMENT;
				}
			}
			else if ((*_line).find("#include") != std::string::npos)
			{
				uint _first = (*_line).find('\"', 0);
				uint _second = (*_line).find('\"', _first + 1);

				if ((_second - _first - 1) <= 0)
				{
					ERROR("Error parsing line: \"" << (*_line) << "\"");
				}

				// TODO: fix relative paths
				std::string _filePath = ROOT_SHADER + (*_line).substr(_first + 1, _second - _first - 1);
				_streams.push_back({ std::ifstream(_filePath), "" });
				_currIndex++;
			}
			else if (_type != ShaderType::NONE)
			{
				_ss[(int)_type] << (*_line) << std::endl;
			}
		}

		return { _ss[0].str(), _ss[1].str() };
	}

	bool Shader::attachShader(const char * fileText, GLuint type)
	{
		GL(GLuint _shader = glCreateShader(type));

		if (_shader == 0)
		{
			ERROR("Shader creation failed. Could not find valid memory location in constructor");
			return false;
		}

		GL(glShaderSource(_shader, 1, &fileText, 0));
		GL(glCompileShader(_shader));

		GLint _success;
		GL(glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success));
		if (!_success)
		{
			logShaderInfo(_shader);
			return false;
		}

		GL(glAttachShader(m_ProgramID, _shader));
		GL(glDeleteShader(_shader));
		return true;
	}

	bool Shader::compileProgram(void)
	{
		GL(glLinkProgram(m_ProgramID));
		GL(glValidateProgram(m_ProgramID));

		GLint _status = -1;
		GL(glGetProgramiv(m_ProgramID, GL_VALIDATE_STATUS, &_status));
		if (_status == GL_FALSE)
		{
			logProgramInfo(m_ProgramID);
			return false;
		}

		return true;
	}
} // namespace gg
