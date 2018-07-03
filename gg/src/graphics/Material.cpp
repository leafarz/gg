#include "graphics/Material.h"

#include "debug/Log.h"
#include "graphics/RenderTarget.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace gg { namespace graphics {
	Material::Material(void)
	{ }

	Material::Material(Shader* shader)
		: m_Shader(shader)
	{ }

	// TODO: add reference count for shader for delete
	Material::~Material(void)
	{ }

	void Material::setShader(Shader * shader)
	{
		m_Shader = shader;
	}

	void Material::setTexture(const std::string& key, Texture* texture)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Textures.push(Data<Texture*>(key, texture));
	}

	void Material::setTexture(const std::string& prefix, RenderTarget* renderTarget)
	{
		std::string _key1 = prefix + "_ColorTexture";
		std::string _key2 = prefix + "_DepthTexture";
		bool _hasUniform = false;

		if (m_Shader->hasUniform(_key1))
		{
			_hasUniform = true;
			m_Textures.push(Data<Texture*>(_key1, renderTarget->getColorTexture()));
		}

		if (m_Shader->hasUniform(_key2))
		{
			_hasUniform = true;
			m_Textures.push(Data<Texture*>(_key2, renderTarget->getDepthTexture()));
		}

		if (!_hasUniform)
		{
			WARN("No uniform with keys [" << _key1 << "] and [" << _key2 << ']');
		}
	}

	void Material::setUniformf(const std::string& key, float val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Floats.push(Data<float>(key, val));
	}
	void Material::setUniform(const std::string& key, const math::Color& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<math::Vec4f>(key, math::Vec4f(val.r, val.g, val.b, val.a)));
	}
	void Material::setUniform(const std::string& key, const math::Vec3f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec3fs.push(Data<math::Vec3f>(key, val));
	}
	void Material::setUniform(const std::string& key, float x, float y, float z)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec3fs.push(Data<math::Vec3f>(key, math::Vec3f(x, y, z)));
	}
	void Material::setUniform(const std::string& key, const math::Vec4f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<math::Vec4f>(key, val));
	}
	void Material::setUniform(const std::string& key, float x, float y, float z, float w)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<math::Vec4f>(key, math::Vec4f(x, y, z, w)));
	}
	void Material::setUniform(const std::string& key, const math::Mat4f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Mat4fs.push(Data<math::Mat4f>(key, val));
	}

	void Material::bind(void) const { m_Shader->bind(); }
	void Material::unbind(void) const { m_Shader->unbind(); }

	void Material::updateUniforms(void)
	{
		int _samplerSlot = 0;
		while (!m_Textures.empty())
		{
			Data<Texture*>& _top = m_Textures.top();
			Texture* _tex = _top.val;
			_tex->bind(_samplerSlot);
			m_Shader->setUniformi(_top.key, _samplerSlot);
			m_Textures.pop();
			_samplerSlot++;
		}
		while (!m_Floats.empty())
		{
			Data<float>& _top = m_Floats.top();
			m_Shader->setUniformf(_top.key, _top.val);
			m_Floats.pop();
		}
		while (!m_Vec3fs.empty())
		{
			Data<math::Vec3f>& _top = m_Vec3fs.top();
			m_Shader->setUniform(_top.key, _top.val);
			m_Vec3fs.pop();
		}
		while (!m_Vec4fs.empty())
		{
			Data<math::Vec4f>& _top = m_Vec4fs.top();
			m_Shader->setUniform(_top.key, _top.val);
			m_Vec4fs.pop();
		}
		while (!m_Mat4fs.empty())
		{
			Data<math::Mat4f>& _top = m_Mat4fs.top();
			m_Shader->setUniform(_top.key, _top.val, true);
			m_Mat4fs.pop();
		}
	}
}/*namespace graphics*/ } // namespace gg
