#ifndef		GGENGINE_SHADER_H
#define		GGENGINE_SHADER_H
#pragma once

#include "GL/glew.h"
#include <unordered_map>
#include <string>

#include "math/Vec3f.h"
#include "math/Mat4f.h"

namespace GGEngine
{
	class Shader
	{
	private:
		struct ShaderData
		{
			std::string vsString;
			std::string fsString;
			ShaderData(const std::string& vsString, const std::string& fsString)
			{
				this->vsString = vsString;
				this->fsString = fsString;
			}
		};
		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1, LENGTH
		};

	public:
		Shader(const std::string& file);
		~Shader(void);

		void bind(void);

		void setUniformi(const std::string& key, GLuint val);
		void setUniformf(const std::string& key, GLfloat val);
		void setUniform(const std::string& key, Math::Vec3f val);
		void setUniform(const std::string& key, Math::Mat4f val, GLboolean transpose);
		void setUniform(const std::string& key, GLfloat* val, GLboolean transpose);

	private:
		Shader(void) = delete;

		static void logShaderInfo(GLuint shader);
		static void logProgramInfo(GLuint program);

		ShaderData parseShader(const char* file);
		bool attachShader(const char* fileText, GLuint type);

		bool compileProgram(void);

		void addAllUniforms(void);


	private:
		static std::unordered_map<unsigned int, GLuint> s_ShaderHash;

		GLuint m_ProgramID;


	}; // class Shader
} // namespace GGEngine

#endif
