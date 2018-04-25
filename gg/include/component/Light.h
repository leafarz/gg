#ifndef		GG_LIGHT_H
#define		GG_LIGHT_H
#pragma once

#include "component/Component.h"
#include "core/Types.h"

#include "math/Color.h"
#include "math/MathUtil.h"
#include "math/Vec4f.h"
namespace gg
{
	namespace graphics { class Renderer; }
	class Light : public Component
	{
	private:
		friend class graphics::Renderer;

	private:
		enum class DirtyBits : ubyte
		{
			Intensity	= 1 << 0,
			Color		= 1 << 1,
			Angle		= 1 << 2,
			Attenuation	= 1 << 3
		};
	public:
		enum class LightType : ubyte
		{
			DirectionalLight,
			SpotLight,
			PointLight
		};
	public:
		// TODO: add template lighttype
		Light(LightType lightType);
		Light(LightType lightType, float intensity, const math::Color& color, float angle, const math::Vec3f& attenuation);
		~Light(void);

		static ComponentType getStaticType(void) { return ComponentType::Light; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setLightType(LightType lightType)
		{
			m_LightType = lightType;

			switch(lightType)
			{
			case LightType::DirectionalLight:
				break;
			case LightType::PointLight:
				m_Angle = 180;
				break;
			case LightType::SpotLight:
				m_Angle = math::clamp(m_Angle, 0, 89);
				break;
			}
		}

		LightType getLightType(void) const { return m_LightType; }

		const math::Color& getColor(void) const { return m_Color; }
		void setColor(math::Color color);

		const float getIntensity(void) const { return m_Intensity; }
		void setIntensity(float intensity);

		const float getAngle(void) const { return m_Angle; }
		void setAngle(float angle);

		const math::Vec3f& getAttenuation(void) const { return m_Attenuation; }
		void setAttenuation(float constant, float linear, float exponential);
		void setAttenuation(const math::Vec3f& attenuation);

	private:
		void setDirty(DirtyBits bit);
		void clearDirty(void);
		void clearDirty(DirtyBits bit);
		bool isDirty(DirtyBits bit) const;

	private:
		DirtyBits m_DirtyBits = static_cast<DirtyBits>(
			(ubyte)DirtyBits::Intensity |
			(ubyte)DirtyBits::Color |
			(ubyte)DirtyBits::Angle |
			(ubyte)DirtyBits::Attenuation
		);

		LightType m_LightType;

		float m_Intensity;
		math::Color m_Color;
		float m_Angle;
		math::Vec3f m_Attenuation;
	};
} // namespace gg

#endif
