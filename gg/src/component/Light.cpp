#include "component/Light.h"

#include "component/Transform.h"
#include "entity/GameObject.h"
namespace gg
{
	Light::Light(Light::LightType lightType)
		: m_LightType(lightType)
	{
		if (lightType == LightType::PointLight) { m_Angle = 180; }
	}

	Light::~Light(void)
	{
	}
	void Light::setColor(Color color) { m_Color = color; }
	void Light::setAngle(float angle)
	{
		if (m_LightType == LightType::PointLight) { return; }
		m_Angle = angle;
	}
	void Light::setAttenuation(float constant, float linear, float exponential) { m_Attenuation.set(constant, linear, exponential); }
	void Light::setAttenuation(const Math::Vec3f& attenuation) { m_Attenuation = attenuation; }
} // namespace gg
