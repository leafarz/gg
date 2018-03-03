#include "graphics/Renderer.h"

#include "platform/opengl/GLCommon.h"

#include "core/Time.h"

#include "component/Light.h"

#include "entity/GameObject.h"

#include "graphics/Material.h"
#include "graphics/Shader.h"

#include "util/Iterators.h"

namespace gg
{
	Renderer::Renderer(void)
	{
		GL(glFrontFace(GL_CW));
		GL(glCullFace(GL_BACK));
		GL(glEnable(GL_CULL_FACE));
		GL(glEnable(GL_DEPTH_TEST));
		GL(glEnable(GL_TEXTURE_2D));
		GL(glClearColor(0.1, 0.1, 0.3, 0.0));
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

	void Renderer::draw(
		GameObject* gameObject,
		const Math::Mat4f& viewMatrix,
		const Math::Mat4f& projectionMatrix,
		const Math::Mat4f& pvMatrix,
		const LightSettings& lightSettings,
		const std::vector<Light*>& lights)
	{
		MeshRenderer* _mr = gameObject->getComponent<MeshRenderer>();
		if (!_mr) { return; }

		Material* _mat = _mr->getMaterial();
		if (!_mat) { return; }

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
			case Shader::SystemUniform::TIME:
			{
				_mat->setUniformf(Shader::systemUniformEnumToString(*it), static_cast<float>(Time::getCurrentTime()));
				break;
			}
			case Shader::SystemUniform::AMBIENT:
			{
				_mat->setUniform(Shader::systemUniformEnumToString(*it), lightSettings.ambientColor);
				break;
			}
			case Shader::SystemUniform::LIGHT:
			{
				int _index = 0;
				VFOR(it2, lights)
				{
					switch ((*it2)->getLightType())
					{
					case Light::LightType::DirectionalLight:
					{
						Transform* _t = (*it2)->getGameObject()->getTransform();
						Math::Vec4f _pos(_t->getPosition(), 0);
						Math::Vec3f _forward = _t->getForward();

						// color, position, direction
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 +  (int)(SystemLightIndex::Color)], (*it2)->getColor());
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Direction)], _forward);
						break;
					}
					case Light::LightType::PointLight:
					{
						Math::Vec4f _pos((*it2)->getGameObject()->getTransform()->getPosition(), 1);
						const Math::Vec3f& _attenuation = (*it2)->getAttenuation();

						// color, position, angle, attenuation
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Color)], (*it2)->getColor());
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Angle)], (*it2)->getAngle());
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
						break;
					}
					case Light::LightType::SpotLight:
					{
						Transform* _t = (*it2)->getGameObject()->getTransform();
						Math::Vec4f _pos(_t->getPosition(), 1);
						const Math::Vec3f& _attenuation = (*it2)->getAttenuation();

						// color, position, direction, angle, attenuation
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Color)], (*it2)->getColor());
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
						_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Direction)], _t->getForward());
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Angle)], (*it2)->getAngle());
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
						break;
					}
					}
					_index++;
				}
				break;
			}
			}
		}
		_mr->draw();
	}

} // namespace gg
