#include "graphics/Renderer.h"

#include "platform/opengl/GLCommon.h"

#include "core/Time.h"

#include "component/Light.h"

#include "entity/GameObject.h"

#include "graphics/Material.h"
#include "graphics/Shader.h"

#include "util/Iterators.h"

namespace gg { namespace graphics {
	Renderer::Renderer(void)
	{
		GL(glFrontFace(GL_CW));
		GL(glCullFace(GL_BACK));
		GL(glEnable(GL_CULL_FACE));
		GL(glEnable(GL_DEPTH_TEST));
		GL(glEnable(GL_TEXTURE_2D));
		GL(glClearColor(0.1f, 0.1f, 0.3f, 0.0f));

		m_DebugLine = new graphics::DebugLine();
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
		const Math::Vec3f& cameraPosition,
		const Math::Vec3f& cameraDirection,
		const LightSettings& lightSettings,
		const std::vector<Light*>& lights)
	{
		MeshRenderer* _mr = gameObject->getComponent<MeshRenderer>();
		if (!_mr) { return; }

		Material* _mat = _mr->getMaterial();
		if (!_mat) { return; }

		const std::vector<Shader::SystemUniform>& _sysUniforms = _mat->getShader()->getSystemUniforms();

		Transform* _t = gameObject->getTransform();
		VFOR(it, _sysUniforms)
		{
			switch (*it)
			{
			case Shader::SystemUniform::MODEL:
			{
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
			case Shader::SystemUniform::CAMERA_POSITION:
			{
				_mat->setUniform(Shader::systemUniformEnumToString(*it), cameraPosition);
				break;
			}
			case Shader::SystemUniform::CAMERA_DIRECTION:
			{
				_mat->setUniform(Shader::systemUniformEnumToString(*it), cameraDirection);
				break;
			}
			case Shader::SystemUniform::LIGHT:
			{
				int _index = 0;
				VFOR(it2, lights)
				{
					Light* _light = *it2;
					Transform* _tLight = _light->getGameObject()->getTransform();

					if (_light->isDirty(Light::DirtyBits::Intensity))
					{
						_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Intensity)], _light->getIntensity());
						_light->clearDirty(Light::DirtyBits::Intensity);
					}

					switch (_light->getLightType())
					{
					case Light::LightType::DirectionalLight:
					{
						// color, position, direction
						if(_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							Math::Vec4f _pos(_tLight->getPosition(), 0);
							Math::Vec3f _forward = _tLight->getForward();
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Direction)], _forward);
						}
						break;
					}
					case Light::LightType::PointLight:
					{
						// color, position, angle, attenuation
						if (_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							Math::Vec4f _pos(_tLight->getPosition(), 1);
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
						}

						if (_light->isDirty(Light::DirtyBits::Angle))
						{
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Angle)], _light->getAngle());
							_light->clearDirty(Light::DirtyBits::Angle);
						}

						if (_light->isDirty(Light::DirtyBits::Attenuation))
						{
							const Math::Vec3f& _attenuation = _light->getAttenuation();
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
							_light->clearDirty(Light::DirtyBits::Attenuation);
						}
						break;
					}
					case Light::LightType::SpotLight:
					{
						// color, position, direction, angle, attenuation
						if (_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							Math::Vec4f _pos(_tLight->getPosition(), 1);
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Position)], _pos);
							_mat->setUniform(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Direction)], _tLight->getForward());
						}

						if (_light->isDirty(Light::DirtyBits::Angle))
						{
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::Angle)], _light->getAngle());
							_light->clearDirty(Light::DirtyBits::Angle);
						}

						if (_light->isDirty(Light::DirtyBits::Attenuation))
						{
							const Math::Vec3f& _attenuation = _light->getAttenuation();
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
							_mat->setUniformf(m_SystemLightPrefixes[_index * 8 + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
							_light->clearDirty(Light::DirtyBits::Attenuation);
						}
						break;
					}
					}
					_index++;
				} // VFOR it2
				break;
			}
			}
		} // VFOR it

		// TODO: check if light might be cleared while objects are not yet finished
		// eg. GameObjects[]
		// dLight, box, pLight, box2
		_t->clearDirty();
		_mr->draw();
	}

	/* Debug Line */
	void Renderer::drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color)
	{
		if (m_DrawLineCount < m_LineQueue.size())
		{
			m_LineQueue[m_DrawLineCount].from = from;
			m_LineQueue[m_DrawLineCount].to = to;
			m_LineQueue[m_DrawLineCount].color = color;
		}
		else
		{
			m_LineQueue.push_back({ from, to, color });
		}
		m_DrawLineCount++;
	}

	void Renderer::drawDebug(const Math::Mat4f& pvMatrix)
	{
		// nothing to draw
		if (m_DrawLineCount == 0) { return; }

		m_DebugLine->begin(pvMatrix);
		FORU(i, 0, m_DrawLineCount)
		{
			const LineData& _data = m_LineQueue[i];
			m_DebugLine->drawLine(_data.from, _data.to, _data.color);
		}
		m_DrawLineCount = 0;
	}
}/*namespace graphics*/ } // namespace gg
