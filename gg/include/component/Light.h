#ifndef		GG_LIGHT_H
#define		GG_LIGHT_H
#pragma once

#include "component/Component.h"
#include "core/Types.h"

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
		Light(LightType lightType);
		~Light(void);

		LightType getLightType(void) const { return m_LightType; }

	private:
		LightType m_LightType;
	}; // class Light
} // namespace gg

#endif
