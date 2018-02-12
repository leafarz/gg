#include "graphics/Renderer.h"

#include "platform/opengl/GLCommon.h"
#include "entity/GameObject.h"
#include "graphics/Material.h"
#include "graphics/Shader.h"

#include "core/gg.h"
namespace gg
{
	Renderer::Renderer(void)
	{
		GL(glFrontFace(GL_CW));
		GL(glCullFace(GL_BACK));
		GL(glEnable(GL_CULL_FACE));
		GL(glEnable(GL_DEPTH_TEST));
	}

	Renderer::~Renderer(void)
	{
	}

	void Renderer::begin(void) const
	{
		GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL(glEnable(GL_BLEND));
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
