#ifndef		GG_MATERIAL_H
#define		GG_MATERIAL_H
#pragma once

#include <stack>
#include "math/Color.h"
#include "math/Vec3f.h"
#include "math/Mat4f.h"

#include "core/Types.h"

namespace gg { namespace graphics { class RenderTarget; class Shader; class Texture; } }

namespace gg { namespace graphics {
	class Material
	{
	private:
		friend class MeshRenderer;
		friend class Renderer;

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
		Material(Shader* shader);
		~Material(void);

		Shader* getShader(void) const;
		void setShader(Shader* shader);

		// currently no setUniformi and is replaced by setTexture

		void setTexture(const std::string& key, Texture* texture);
		/* Sets Rendertarget with prefix and predetermined suffixes.
		 * Uniform variable format in the shader should be
		 * [prefix]_ColorTexture & [prefix]_DepthTexture in order to work
		 */
		void setTexture(const std::string& prefix, RenderTarget* renderTarget);
		void setUniformf(const std::string& key, float val);
		void setUniform(const std::string& key, const math::Color& val);
		void setUniform(const std::string& key, const math::Vec3f& val);
		void setUniform(const std::string& key, float x, float y, float z);
		void setUniform(const std::string& key, const math::Vec4f& val);
		void setUniform(const std::string& key, float x, float y, float z, float w);
		void setUniform(const std::string& key, const math::Mat4f& val);

	private:
		void bind(void) const;
		void unbind(void) const;

		void updateUniforms(void);

	private:
		Shader* m_Shader;

		std::stack<Data<Texture*>> m_Textures;
		std::stack<Data<float>> m_Floats;
		std::stack<Data<math::Vec3f>> m_Vec3fs;
		std::stack<Data<math::Vec4f>> m_Vec4fs;
		std::stack<Data<math::Mat4f>> m_Mat4fs;

	}; // class Material
}/*namespace graphics*/ } // namespace gg

#endif
