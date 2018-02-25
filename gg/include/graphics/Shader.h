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
		friend class Material;
		friend class Renderer;

		enum class ShaderType : int8
		{
			NONE		= -1,
			VERTEX		=  0,
			FRAGMENT	=  1,
			LENGTH
		};
		enum class DataType : ubyte
		{
			INT			= 0,
			FLOAT		= 1,
			VEC2		= 2,
			VEC3		= 3,
			VEC4		= 4,
			MAT3		= 5,
			MAT4		= 6,
			SAMPLER2D	= 7,
			UNKNOWN		= 8
		};
		enum class SystemUniform : ubyte
		{
			MODEL,
			VIEW,
			PROJECTION,
			MVP,
			TIME,
			AMBIENT,
			LIGHT,
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
			DataType dataType;
			GLint loc;
			UniformData(void)
			{ }
			UniformData(DataType dataType, GLint loc)
				: dataType(dataType), loc(loc)
			{ }
		};

	public:
		Shader(const std::string& filePath);
		~Shader(void);

		std::vector<std::string> getUniforms(void) const;
		bool hasUniform(const std::string& key) const;

		// TODO: temporarily public
		void reload(void);
	private:
		Shader(void) = delete;

		// convertions
		static DataType glEnumToDataType(GLenum type);
		static GLenum dataTypeToGLEnum(DataType dataType);
		static std::string dataTypeToString(DataType dataType);
		static std::string shaderEnumToString(GLenum type);
		static SystemUniform systemUniformStringToEnum(const char* systemUniform);
		static std::string systemUniformEnumToString(SystemUniform type);

		static void logShaderInfo(GLuint shader, GLenum type);
		static void logProgramInfo(GLuint program);

		const UniformData* getUniform(const std::string& key);
		inline const std::vector<SystemUniform>& getSystemUniforms(void) const { return m_SystemUniforms; };

		void bind(void) const;
		void unbind(void) const;

		void loadShader(const std::string& filePath);

		void updateID(void);

	private:

		ShaderData parseShader(const char* file);
		bool attachShader(const char* fileText, GLuint type);

		bool compileProgram(void);

		void addAllUniforms(void);

		void setUniformi(const std::string& key, int val);
		void setUniformf(const std::string& key, float val);
		void setUniform(const std::string& key, const Math::Vec3f& val);
		void setUniform(const std::string& key, float x, float y, float z);
		void setUniform(const std::string& key, const Math::Vec4f& val);
		void setUniform(const std::string& key, float x, float y, float z, float w);
		void setUniform(const std::string& key, const Math::Mat4f& val, bool transpose);
		void setUniform(const std::string& key, float* val, bool transpose);

		void setUniformi(int loc, int val);
		void setUniformf(int loc, float val);
		void setUniform(int loc, const Math::Vec3f& val);
		void setUniform(int loc, float x, float y, float z);
		void setUniform(int loc, const Math::Mat4f& val, bool transpose);
		void setUniform(int loc, float* val, bool transpose);

	private:
		/* Key value pairs of hash to ids created throughout the app. */
		static std::unordered_map<uint, GLuint> s_ShaderHash;

		/* Program id created by OpenGL command.*/
		GLuint m_ID;

		/* Hash of the filepath. */
		uint m_ShaderHash;
		std::unordered_map<GLuint, uint> m_ShaderIDs;
		std::string m_FilePath;

		std::unordered_map<std::string, UniformData> m_Uniforms;
		std::vector<SystemUniform> m_SystemUniforms;


	}; // class Shader
} // namespace gg

#endif
