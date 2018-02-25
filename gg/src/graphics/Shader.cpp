#include "graphics/Shader.h"

#include <fstream>
#include <sstream>

#include "Paths.h"

#include "platform/opengl/GLCommon.h"

#include "debug/Log.h"
#include "security/cryptography/crc32.h"
#include "util/Iterators.h"

namespace gg
{
	std::unordered_map<uint, GLuint> Shader::s_ShaderHash;

	Shader::Shader(const std::string& filePath)
		: m_FilePath(filePath)
	{
		_SYS("Processing file: \"" << m_FilePath << "\"");
		// check first if file is already cached
		m_ShaderHash = Crc32::getHash(m_FilePath.c_str(), m_FilePath.size());
		bool _isCached = s_ShaderHash.find(m_ShaderHash) != s_ShaderHash.end();

		if (_isCached)
		{
			_SYS("Fetching cached shader: \"" << m_FilePath << "\"");
			m_ID = s_ShaderHash[m_ShaderHash];
			return;
		}

		loadShader(filePath);
		addAllUniforms();

		s_ShaderHash[m_ShaderHash] = m_ID;
	}

	Shader::~Shader(void)
	{
		GL(glDetachShader(m_ID, GL_VERTEX_SHADER));
		GL(glDetachShader(m_ID, GL_FRAGMENT_SHADER));

		GL(glDeleteProgram(m_ID));
	}

	std::vector<std::string> Shader::getUniforms(void) const
	{
		std::vector<std::string> _keys;
		_keys.reserve(m_Uniforms.size());

		for (auto kv : m_Uniforms) { _keys.push_back(kv.first); }

		return _keys;
	}

	bool Shader::hasUniform(const std::string& key) const
	{
		return m_Uniforms.find(key) != m_Uniforms.end();
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

	std::string Shader::shaderEnumToString(GLenum type)
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:			return "VertexShader";
		case GL_FRAGMENT_SHADER:		return "FragmentShader";
		}
		return "unknown";
	}

	Shader::SystemUniform Shader::systemUniformStringToEnum(const char* systemUniform)
	{
		if		(strcmp(systemUniform, "sys_M") == 0)				{ return SystemUniform::MODEL; }
		else if (strcmp(systemUniform, "sys_V") == 0)				{ return SystemUniform::VIEW; }
		else if (strcmp(systemUniform, "sys_P") == 0)				{ return SystemUniform::PROJECTION; }
		else if (strcmp(systemUniform, "sys_MVP") == 0)				{ return SystemUniform::MVP; }
		else if (strcmp(systemUniform, "sys_Time") == 0)			{ return SystemUniform::TIME; }
		else if (strcmp(systemUniform, "sys_AmbientColor") == 0)	{ return SystemUniform::AMBIENT; }
		return SystemUniform::UNKNOWN;
	}

	std::string Shader::systemUniformEnumToString(SystemUniform type)
	{
		switch (type)
		{
		case SystemUniform::MODEL:			return "sys_M";
		case SystemUniform::VIEW:			return "sys_V";
		case SystemUniform::PROJECTION:		return "sys_P";
		case SystemUniform::MVP:			return "sys_MVP";
		case SystemUniform::TIME:			return "sys_Time";
		case SystemUniform::AMBIENT:		return "sys_AmbientColor";
		}
		return "";
	}

	void Shader::logShaderInfo(GLuint shader, GLenum type)
	{
		char _infoLog[512];
		GL(glGetShaderInfoLog(shader, 512, NULL, _infoLog));
		ERROR("[" << shaderEnumToString(type) << " Error]" << " compilation failed!\n" << _infoLog);
	}

	GLvoid Shader::logProgramInfo(GLuint program)
	{
		char _infoLog[512];
		GL(glGetProgramInfoLog(program, 512, NULL, _infoLog));
		ERROR("[Error] Invalid program!\n" << _infoLog);
	}

	const Shader::UniformData* Shader::getUniform(const std::string & key)
	{
		return m_Uniforms.find(key) != m_Uniforms.end() ? &m_Uniforms[key] : nullptr;
	}

	void Shader::bind(void) const { GL(glUseProgram(s_ShaderHash[m_ShaderHash])); }
	void Shader::unbind(void) const { GL(glUseProgram(0)); }

	void Shader::loadShader(const std::string& filePath)
	{
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

		GL(m_ID = glCreateProgram());
		if (m_ID == 0)
		{
			ERROR("Shader program creation failed. Could not find valid memory location in constructor");
			return;
		}
		_SYS("Creating vertex shader");
		if (!attachShader(_vsChar, GL_VERTEX_SHADER)) { return; }
		_SYS("Creating fragment shader");
		if (!attachShader(_fsChar, GL_FRAGMENT_SHADER)) { return; }
		_SYS("Compiling program");
		if (!compileProgram()) { return; }
	}

	void Shader::reload(void)
	{
		_SYS("Reloading shader: \"" << m_FilePath << "\"");
		m_Uniforms.clear();
		m_SystemUniforms.clear();

		GL(glDeleteProgram(m_ID));
		loadShader(m_FilePath);
		addAllUniforms();

		s_ShaderHash[m_ShaderHash] = m_ID;
	}

	void Shader::updateID(void)
	{
		m_ID = s_ShaderHash[m_ShaderHash];
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
		if (m_ShaderIDs.find(type) != m_ShaderIDs.end())
		{
			ERROR("Shader creation failed. Program already has " << shaderEnumToString(type));
		}
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
			logShaderInfo(_shader, type);
			return false;
		}

		GL(glAttachShader(m_ID, _shader));
		GL(glDeleteShader(_shader));

		m_ShaderIDs[type] = _shader;
		return true;
	}

	bool Shader::compileProgram(void)
	{
		GL(glLinkProgram(m_ID));
		GL(glValidateProgram(m_ID));

		GLint _status = -1;
		GL(glGetProgramiv(m_ID, GL_VALIDATE_STATUS, &_status));
		if (_status == GL_FALSE)
		{
			logProgramInfo(m_ID);
			return false;
		}

		return true;
	}

	void Shader::addAllUniforms(void)
	{
		int _count = 0;
		int _len = -1;
		int _num = -1;
		GLenum _type = GL_ZERO;
		char _name[256];

		GL(glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &_count));
		FORU(i, 0, (uint)_count)
		{
			GL(glGetActiveUniform(m_ID, i, sizeof(_name) - 1, &_len, &_num, &_type, _name));
			GL(GLint _uniformLoc = glGetUniformLocation(m_ID, _name));

			DataType _dataType = glEnumToDataType(_type);
			if (_dataType == DataType::UNKNOWN)
			{
				ERROR("The uniform [" << _name << "] is of an unknown type! (" << _type << ")");
			}
			else
			{
				_SYS("Adding uniform (" << _uniformLoc << ") <" << dataTypeToString(glEnumToDataType(_type)) << "> " << _name);
				if (_len > 4)
				{
					SystemUniform _systemUniform = systemUniformStringToEnum(_name);
					if (_systemUniform != SystemUniform::UNKNOWN) { m_SystemUniforms.push_back(_systemUniform); }
				}
				m_Uniforms[_name] = UniformData(glEnumToDataType(_type), _uniformLoc);
			}
		}
	}

	GLvoid Shader::setUniformi(const std::string& key, int val)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [sampler2D][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::SAMPLER2D)
		{
			WARN("Uniform mismatch!\nTrying to set sampler2D value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		GL(glUniform1i(_uniformData->loc, val));
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
		GL(glUniform1f(_uniformData->loc, val));
	}

	GLvoid Shader::setUniform(const std::string& key, const Math::Vec3f& val)
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
		GL(glUniform3f(_uniformData->loc, val.x, val.y, val.z));
	}

	void Shader::setUniform(const std::string& key, float x, float y, float z)
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
		GL(glUniform3f(_uniformData->loc, x, y, z));
	}

	void Shader::setUniform(const std::string & key, const Math::Vec4f & val)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [vec4][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::VEC4)
		{
			WARN("Uniform mismatch!\nTrying to set vec4 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		GL(glUniform4f(_uniformData->loc, val.x, val.y, val.z, val.w));
	}

	void Shader::setUniform(const std::string & key, float x, float y, float z, float w)
	{
		const UniformData* _uniformData = getUniform(key);
		if (_uniformData == nullptr)
		{
			WARN("No uniform [vec4][" << key << "] found");
			return;
		}
		else if (_uniformData->dataType != DataType::VEC4)
		{
			WARN("Uniform mismatch!\nTrying to set vec4 value for [" + dataTypeToString(_uniformData->dataType) + "][" << key << "]!");
			return;
		}
		GL(glUniform4f(_uniformData->loc, x, y, z, w));
	}

	GLvoid Shader::setUniform(const std::string& key, const Math::Mat4f& val, bool transpose)
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

		GL(glUniformMatrix4fv(_uniformData->loc, 1, transpose, val.getMatrix()));
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
		GL(glUniformMatrix4fv(_uniformData->loc, 1, transpose, val));
	}

	void Shader::setUniformi(int loc, int val) { GL(glUniform1i(loc, val)); }
	void Shader::setUniformf(int loc, float val) { GL(glUniform1f(loc, val)); }
	void Shader::setUniform(int loc, const Math::Vec3f& val) { GL(glUniform3f(loc, val.x, val.y, val.z)); }
	void Shader::setUniform(int loc, float x, float y, float z) { GL(glUniform3f(loc, x, y, z)); }
	void Shader::setUniform(int loc, const Math::Mat4f& val, bool transpose) { GL(glUniformMatrix4fv(loc, 1, transpose, val.getMatrix())); }
	void Shader::setUniform(int loc, float * val, bool transpose) { GL(glUniformMatrix4fv(loc, 1, transpose, val)); }
} // namespace gg
