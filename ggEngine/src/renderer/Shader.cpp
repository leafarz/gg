#include "renderer/Shader.h"

#include "core/gg.h"
#include <fstream>
#include <sstream>
#include "security/cryptography/crc32.h"
#include "platform/opengl/GLCommon.h"

namespace gg
{
	std::unordered_map<unsigned int, GLuint> Shader::s_ShaderHash;

	Shader::Shader(const std::string& file)
	{
		// check first if file is already cached
		int _hash = Crc32::getHash(file.c_str(), file.size());
		bool _isCached = s_ShaderHash.find(_hash) != s_ShaderHash.end();

		if (_isCached)
		{
			m_ProgramID = s_ShaderHash[_hash];
			return;
		}

		ShaderData _data = parseShader(file.c_str());
		if (_data.vsString.empty())
		{
			WARN("No vertex shader found in\n:[" << file << "]!");
			return;
		}
		if (_data.fsString.empty())
		{
			WARN("No fragment shader found in\n:[" << file << "]!");
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
		for (int i = 0; i < _size; i++)
		{
			glGetActiveUniform(m_ProgramID, i, sizeof(_name) - 1, &_len, &_num, &_type, _name);
			// TODO: add uniforms
		}
	}

	GLvoid Shader::setUniformi(const std::string& key, GLuint val)
	{
		//glUniform1i(this->shaderResource->getUniform(key), val);
	}

	GLvoid Shader::setUniformf(const std::string& key, GLfloat val)
	{
		//glUniform1f(this->shaderResource->getUniform(key), val);
	}

	GLvoid Shader::setUniform(const std::string& key, Math::Vec3f val)
	{
		//glUniform3f(this->shaderResource->getUniform(key), val.x, val.y, val.z);
	}

	GLvoid Shader::setUniform(const std::string& key, Math::Mat4f val, GLboolean transpose)
	{
		//glUniformMatrix4fv(this->shaderResource->getUniform(key), 1, transpose, val.getMatrix());
	}

	GLvoid Shader::setUniform(const std::string& key, GLfloat* val, GLboolean transpose)
	{
		//glUniformMatrix4fv(this->shaderResource->getUniform(key), 1, transpose, val);
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

	Shader::ShaderData Shader::parseShader(const char* file)
	{
		std::ifstream _stream(file);
		std::string _line;
		std::stringstream _ss[2];

		ShaderType _type = ShaderType::NONE;

		while (std::getline(_stream, _line))
		{
			if (_line.find("#shader") != std::string::npos)
			{
				if (_line.find("vertex") != std::string::npos)
				{
					_type = ShaderType::VERTEX;
				}
				else if (_line.find("fragment") != std::string::npos)
				{
					_type = ShaderType::FRAGMENT;
				}
			}
			else if (_type != ShaderType::NONE)
			{
				_ss[(int)_type] << _line << std::endl;
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
