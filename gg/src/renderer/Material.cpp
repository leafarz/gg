#include "renderer/Material.h"

#include "core/gg.h"
#include "renderer/Shader.h"
namespace gg
{
	Material::Material(void)
	{ }

	Material::Material(Shader* shader)
		: m_Shader(shader)
	{ }

	// TODO: add reference count for shader for delete
	Material::~Material(void)
	{ }

	void Material::bind(void)
	{
		m_Shader->bind();
		
		// TODO: add texture bind
		
		while (!m_Ints.empty())
		{
			Data<int>& _top = m_Ints.top();
			m_Shader->setUniformi(_top.key, _top.val);
			m_Ints.pop();
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
		while (!m_Mat4fs.empty())
		{
			Data<Math::Mat4f>& _top = m_Mat4fs.top();
			m_Shader->setUniform(_top.key, _top.val, true);
			m_Mat4fs.pop();
		}
	}

	void Material::unbind(void) const { m_Shader->unbind(); }

	Shader* Material::getShader(void) const { return m_Shader; }
	void Material::setShader(Shader * shader)
	{
		m_Shader = shader;
	}

	void Material::setUniformi(const std::string& key, int val)
	{
		if (!m_Shader->hasUniform(key)) { return; }
		m_Ints.push(Data<int>(key, val));
	}
	void Material::setUniformf(const std::string& key, float val)
	{
		if (!m_Shader->hasUniform(key)) { return; }
		m_Floats.push(Data<float>(key, val));
	}
	void Material::setUniform(const std::string& key, Math::Vec3f val)
	{
		if (!m_Shader->hasUniform(key)) { return; }
		m_Vec3fs.push(Data<Math::Vec3f>(key, val));
	}
	void Material::setUniform(const std::string& key, float x, float y, float z)
	{
		if (!m_Shader->hasUniform(key)) { return; }
		m_Vec3fs.push(Data<Math::Vec3f>(key, Math::Vec3f(x, y, z)));
	}
	void Material::setUniform(const std::string& key, Math::Mat4f val)
	{
		if (!m_Shader->hasUniform(key)) { return; }
		m_Mat4fs.push(Data<Math::Mat4f>(key, val));
	}
} // namespace gg
