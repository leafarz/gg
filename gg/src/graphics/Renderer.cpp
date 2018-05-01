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
		const math::Mat4f& viewMatrix,
		const math::Mat4f& projectionMatrix,
		const math::Mat4f& pvMatrix,
		const math::Vec3f& cameraPosition,
		const math::Vec3f& cameraDirection,
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
					int _offset = _index * (int)SystemLightIndex::Length;

					if (_light->isDirty(Light::DirtyBits::Intensity))
					{
						_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Intensity)], _light->getIntensity());
						_light->clearDirty(Light::DirtyBits::Intensity);
					}

					if (_light->isDirty(Light::DirtyBits::Specular))
					{
						_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Specular)], _light->getSpecular());
						_light->clearDirty(Light::DirtyBits::Specular);
					}

					switch (_light->getLightType())
					{
					case Light::LightType::DirectionalLight:
					{
						// color, position, direction
						if(_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							math::Vec4f _pos(_tLight->getPosition(), 0);
							math::Vec3f _forward = _tLight->getForward();
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Position)], _pos);
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Direction)], _forward);
						}
						break;
					}
					case Light::LightType::PointLight:
					{
						// color, position, angle, attenuation
						if (_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							math::Vec4f _pos(_tLight->getPosition(), 1);
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Position)], _pos);
						}

						if (_light->isDirty(Light::DirtyBits::Angle))
						{
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Angle)], _light->getAngle());
							_light->clearDirty(Light::DirtyBits::Angle);
						}

						if (_light->isDirty(Light::DirtyBits::Attenuation))
						{
							const math::Vec3f& _attenuation = _light->getAttenuation();
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
							_light->clearDirty(Light::DirtyBits::Attenuation);
						}
						break;
					}
					case Light::LightType::SpotLight:
					{
						// color, position, direction, angle, attenuation
						if (_light->isDirty(Light::DirtyBits::Color))
						{
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Color)], _light->getColor());
							_light->clearDirty(Light::DirtyBits::Color);
						}

						if (_tLight->isDirty())
						{
							math::Vec4f _pos(_tLight->getPosition(), 1);
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Position)], _pos);
							_mat->setUniform(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Direction)], _tLight->getForward());
						}

						if (_light->isDirty(Light::DirtyBits::Angle))
						{
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::Angle)], _light->getAngle());
							_light->clearDirty(Light::DirtyBits::Angle);
						}

						if (_light->isDirty(Light::DirtyBits::Attenuation))
						{
							const math::Vec3f& _attenuation = _light->getAttenuation();
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::ConstantAttenuation)], _attenuation.x);
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::LinearAttenuation)], _attenuation.y);
							_mat->setUniformf(m_SystemLightPrefixes[_offset + (int)(SystemLightIndex::ExponentAttenuation)], _attenuation.z);
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
	void Renderer::drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, uint thickness)
	{
		if (m_LineBuffer.find(thickness) == m_LineBuffer.end())
		{
			m_LineBuffer.insert({ thickness, LineDataGroup({ DebugLine::LineData(from, color), DebugLine::LineData(to, color) }) });
		}
		else
		{
			m_LineBuffer[thickness].add(from, color);
			m_LineBuffer[thickness].add(to, color);
		}										   
	}

	void Renderer::drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, uint thickness, float duration)
	{
		if (m_TimedLineBuffer.find(thickness) == m_TimedLineBuffer.end())
		{
			m_TimedLineBuffer.insert({ thickness, {
				TimedLineData(duration, from, color),
				TimedLineData(duration, to, color)
			} });
		}
		else
		{
			m_TimedLineBuffer[thickness].push_back(TimedLineData(duration, from, color));
			m_TimedLineBuffer[thickness].push_back(TimedLineData(duration, to, color));
		}
	}

	void Renderer::drawDebug(const math::Mat4f& pvMatrix)
	{
		m_DebugLine->begin(pvMatrix);

		UFOR(kv, m_LineBuffer)
		{
			uint _key = kv.first;

			// nothing to draw
			uint _count = m_LineBuffer[_key].getCount();
			if (_count == 0) { continue; }

			m_DebugLine->drawLines(m_LineBuffer[_key].getLineData(), _key, _count);

			m_LineBuffer[_key].resetCount();
		}
		
		UFOR(kv, m_TimedLineBuffer)
		{
			uint _key = kv.first;

			std::vector<TimedLineData>& _array = m_TimedLineBuffer[_key];
			uint _count = _array.size();

			if (_count == 0) { continue; }

			std::vector<DebugLine::LineData> _buffer;
			_buffer.reserve(_count);

			FORU(i, 0, _count)
			{
				_buffer.push_back(_array[i].lineData);
				if ((_array[i].duration-=Time::getDeltaTime()) <= 0)
				{
					_array.erase(_array.begin() + (i==0 ? 0 : i-1));
					--i;
					--_count;
				}
			}

			m_DebugLine->drawLines(_buffer, _key, _buffer.size());
		}

	}
}/*namespace graphics*/ } // namespace gg
