#ifndef		GG_LIGHTSETTINGS_H
#define		GG_LIGHTSETTINGS_H
#pragma once

#include "math/Vec3f.h"

namespace gg { namespace graphics {
	struct LightSettings
	{
	public:
		math::Vec3f ambientColor;

		LightSettings(void)
			: ambientColor(math::Vec3f(0.1f, 0.1f, 0.1f))
		{ }
		LightSettings(const math::Vec3f& ambientColor)
			: ambientColor(ambientColor)
		{ }
	}; // struct LightSettings
}/*namespace graphics*/ } // namespace gg

#endif