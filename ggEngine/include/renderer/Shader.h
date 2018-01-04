#ifndef		GG_SHADER_H
#define		GG_SHADER_H
#pragma once

#include "GL/glew.h"
#include <unordered_map>
#include <string>

#include "core/Types.h"
#include "math/Vec3f.h"
#include "math/Mat4f.h"

namespace gg
{
	class Shader
	{
	private:
		enum class ShaderType : int8
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1, LENGTH
		};
		enum class DataType : byte
		{
			INT,
			FLOAT,
			VEC2,
			VEC3,
			VEC4,
			MAT3,
			MAT4,
			SAMPLER2D,
			UNKNOWN
		};

		struct ShaderData
		{
			std::string vsString;
			std::string fsString;
			ShaderData(const std::string& vsString, const std::string& fsString)
				: vsString(vsString), fsString(fsString)
			{ }
		};
		struct UniformData
		{
			std::string key;
			DataType dataType;
			GLint loc;
			UniformData(const std::string& key, DataType dataType, GLint loc)
				: key(key), dataType(dataType), loc(loc)
			{ }
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

		// convertions
		static DataType glEnumToDataType(GLenum type);
		static GLenum dataTypeToGLEnum(DataType dataType);
		static std::string dataTypeToString(DataType dataType);

		static void logShaderInfo(GLuint shader);
		static void logProgramInfo(GLuint program);

		const UniformData* getUniform(const std::string& key);
		ShaderData parseShader(const char* file);
		bool attachShader(const char* fileText, GLuint type);

		bool compileProgram(void);

		void addAllUniforms(void);


	private:
		static std::unordered_map<uint, GLuint> s_ShaderHash;

		GLuint m_ProgramID;
		uint m_ShaderID;
		std::string m_FileName;

		std::vector<UniformData> m_Uniforms;


	}; // class Shader
} // namespace gg

#endif
