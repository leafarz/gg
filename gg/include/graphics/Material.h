#ifndef		GG_MATERIAL_H
#define		GG_MATERIAL_H
#pragma once

#include <stack>
#include "graphics/Color.h"
#include "math/Vec3f.h"
#include "math/Mat4f.h"

#include "core/Types.h"

namespace gg
{
	namespace graphics { class Texture; class Shader; }
	class Material
	{
	private:
		friend class MeshRenderer;

	private:
		template<typename T>
		struct Data
		{
			std::string key;
			T val;
			Data(const std::string& key, T val)
				: key(key), val(val)
			{ }
		};
		
	public:
		Material(void);
		Material(graphics::Shader* shader);
		~Material(void);

		graphics::Shader* getShader(void) const;
		void setShader(graphics::Shader* shader);

		// currently no setUniformi and is replaced by setTexture

		void setTexture(const std::string& key, graphics::Texture* texture);
		void setUniformf(const std::string& key, float val);
		void setUniform(const std::string& key, const Color& val);
		void setUniform(const std::string& key, const Math::Vec3f& val);
		void setUniform(const std::string& key, float x, float y, float z);
		void setUniform(const std::string& key, const Math::Vec4f& val);
		void setUniform(const std::string& key, float x, float y, float z, float w);
		void setUniform(const std::string& key, const Math::Mat4f& val);

	private:
		void bind(void) const;
		void unbind(void) const;

		void updateUniforms(void);

	private:
		graphics::Shader* m_Shader;

		std::stack<Data<graphics::Texture*>> m_Textures;
		std::stack<Data<float>> m_Floats;
		std::stack<Data<Math::Vec3f>> m_Vec3fs;
		std::stack<Data<Math::Vec4f>> m_Vec4fs;
		std::stack<Data<Math::Mat4f>> m_Mat4fs;

	}; // class Material
} // namespace gg

#endif
