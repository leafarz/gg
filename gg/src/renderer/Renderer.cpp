#include "renderer/Renderer.h"

#include "entity/GameObject.h"
#include "renderer/Material.h"
#include "renderer/Shader.h"

#include "core/gg.h"
namespace gg
{
	Renderer::Renderer(void)
	{
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer(void)
	{
	}

	void Renderer::begin(void) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		// process render commands
	}

	void Renderer::draw(GameObject* gameObject, const Math::Mat4f& viewMatrix, const Math::Mat4f& projectionMatrix, const Math::Mat4f& pvMatrix)
	{
		MeshRenderer* _mr = gameObject->getComponent<MeshRenderer>();
		if (!_mr) { return; }

		Material* _mat = _mr->getMaterial();
		const std::vector<Shader::SystemUniform>& _sysUniforms = _mat->getShader()->getSystemUniforms();

		VFOR(it, _sysUniforms)
		{
			switch (*it)
			{
			case Shader::SystemUniform::MODEL:
			{
				Transform* _t = gameObject->getTransform();
				_mat->setUniform(Shader::systemUniformEnumToString(*it), _t->getTransformationMatrix());
				break;
			}
			case Shader::SystemUniform::VIEW:
			{
				_mat->setUniform(Shader::systemUniformEnumToString(*it), viewMatrix);
				break;
			}
			case Shader::SystemUniform::PROJECTION:
			{
				_mat->setUniform(Shader::systemUniformEnumToString(*it), projectionMatrix);
				break;
			}
			case Shader::SystemUniform::MVP:
			{
				Transform* _t = gameObject->getTransform();
				_mat->setUniform(Shader::systemUniformEnumToString(*it), pvMatrix * _t->getTransformationMatrix());
				break;
			}
			}
		}
		_mr->draw();
	}

} // namespace gg
