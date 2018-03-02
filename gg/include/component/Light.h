#ifndef		GG_LIGHT_H
#define		GG_LIGHT_H
#pragma once

#include "component/Component.h"
#include "core/Types.h"

#include "graphics/Color.h"
#include "math/Vec4f.h"
namespace gg
{
	class Light : public Component
	{
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
		~Light(void);

		static ComponentType getStaticType(void) { return ComponentType::Light; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		LightType getLightType(void) const { return m_LightType; }

		const Color& getColor(void) const			{ return m_Color; }
		void setColor(Color color);

		const float getAngle(void) const				{ return m_Angle; }
		void setAngle(float angle);
		const Math::Vec3f& getAttenuation(void) const	{ return m_Attenuation; }
		void setAttenuation(float constant, float linear, float exponential);
		void setAttenuation(const Math::Vec3f& attenuation);

	private:
		LightType m_LightType;

		Color m_Color;
		float m_Angle;
		Math::Vec3f m_Attenuation;
	}; // class Light
} // namespace gg

#endif
