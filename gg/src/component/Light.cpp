#include "component/Light.h"

#include "component/Transform.h"
#include "entity/GameObject.h"
namespace gg
{
	Light::Light(LightType lightType)
		: m_LightType(lightType), m_Intensity(1), m_Angle(lightType == LightType::PointLight ? 180.0f : 0.0f)
	{ }

	Light::Light(LightType lightType, float intensity, const math::Color& color, float angle, const math::Vec3f & attenuation)
		: m_LightType(lightType), m_Intensity(intensity), m_Color(color), m_Angle(lightType == LightType::PointLight ? 180.0f : angle), m_Attenuation(attenuation)
	{ }

	Light::~Light(void)
	{
	}
	void Light::setColor(math::Color color)
	{
		setDirty(DirtyBits::Color);
		m_Color = color;
	}
	void Light::setIntensity(float intensity)
	{
		setDirty(DirtyBits::Intensity);
		m_Intensity = intensity;
	}
	void Light::setAngle(float angle)
	{
		if (m_LightType == LightType::PointLight) { return; }
		setDirty(DirtyBits::Angle);
		m_Angle = angle;
	}
	void Light::setAttenuation(float constant, float linear, float exponential)
	{
		setDirty(DirtyBits::Attenuation);
		m_Attenuation.set(constant, linear, exponential);
	}
	void Light::setAttenuation(const math::Vec3f& attenuation)
	{
		setDirty(DirtyBits::Attenuation);
		m_Attenuation = attenuation;
	}

	void Light::setDirty(DirtyBits bit)			{ m_DirtyBits = static_cast<DirtyBits>((ubyte)m_DirtyBits | (ubyte)bit); }
	void Light::clearDirty(void)				{ m_DirtyBits = static_cast<DirtyBits>(0); }
	void Light::clearDirty(DirtyBits bit)		{ m_DirtyBits = static_cast<DirtyBits>((ubyte)m_DirtyBits & ~(ubyte)bit); }
	bool Light::isDirty(DirtyBits bit) const	{ return ((ubyte)m_DirtyBits&(ubyte)bit) != 0;	}
} // namespace gg
