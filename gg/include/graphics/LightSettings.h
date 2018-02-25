#ifndef		GG_LIGHTSETTINGS_H
#define		GG_LIGHTSETTINGS_H
#pragma once

#include "math/Vec3f.h"

namespace gg
{
	struct LightSettings
	{
	public:
		Math::Vec3f ambientColor;

		LightSettings(void)
			: ambientColor(Math::Vec3f(0.1f, 0.1f, 0.1f))
		{ }
		LightSettings(const Math::Vec3f& ambientColor)
			: ambientColor(ambientColor)
		{ }
	}; // struct LightSettings
} // namespace gg

#endif