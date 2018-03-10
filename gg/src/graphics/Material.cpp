#include "graphics/Material.h"

#include "debug/Log.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
namespace gg
{
	Material::Material(void)
	{ }

	Material::Material(graphics::Shader* shader)
		: m_Shader(shader)
	{ }

	// TODO: add reference count for shader for delete
	Material::~Material(void)
	{ }

	graphics::Shader* Material::getShader(void) const { return m_Shader; }
	void Material::setShader(graphics::Shader * shader)
	{
		m_Shader = shader;
	}

	void Material::setTexture(const std::string& key, graphics::Texture* texture)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Textures.push(Data<graphics::Texture*>(key, texture));
	}

	void Material::setUniformf(const std::string& key, float val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Floats.push(Data<float>(key, val));
	}
	void Material::setUniform(const std::string& key, const Math::Color& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<Math::Vec4f>(key, Math::Vec4f(val.r, val.g, val.b, val.a)));
	}
	void Material::setUniform(const std::string& key, const Math::Vec3f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec3fs.push(Data<Math::Vec3f>(key, val));
	}
	void Material::setUniform(const std::string& key, float x, float y, float z)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec3fs.push(Data<Math::Vec3f>(key, Math::Vec3f(x, y, z)));
	}
	void Material::setUniform(const std::string& key, const Math::Vec4f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<Math::Vec4f>(key, val));
	}
	void Material::setUniform(const std::string& key, float x, float y, float z, float w)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Vec4fs.push(Data<Math::Vec4f>(key, Math::Vec4f(x, y, z, w)));
	}
	void Material::setUniform(const std::string& key, const Math::Mat4f& val)
	{
		if (!m_Shader->hasUniform(key)) { WARN("No uniform with key [" << key << ']'); return; }
		m_Mat4fs.push(Data<Math::Mat4f>(key, val));
	}

	void Material::bind(void) const { m_Shader->bind(); }
	void Material::unbind(void) const { m_Shader->unbind(); }

	void Material::updateUniforms(void)
	{
		int _samplerSlot = 0;
		while (!m_Textures.empty())
		{
			Data<graphics::Texture*>& _top = m_Textures.top();
			graphics::Texture* _tex = _top.val;
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
			Data<Math::Vec3f>& _top = m_Vec3fs.top();
			m_Shader->setUniform(_top.key, _top.val);
			m_Vec3fs.pop();
		}
		while (!m_Vec4fs.empty())
		{
			Data<Math::Vec4f>& _top = m_Vec4fs.top();
			m_Shader->setUniform(_top.key, _top.val);
			m_Vec4fs.pop();
		}
		while (!m_Mat4fs.empty())
		{
			Data<Math::Mat4f>& _top = m_Mat4fs.top();
			m_Shader->setUniform(_top.key, _top.val, true);
			m_Mat4fs.pop();
		}
	}
} // namespace gg
