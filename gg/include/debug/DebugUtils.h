#ifndef		GG_DEBUGUTILS_H
#define		GG_DEBUGUTILS_H
#pragma once

#include "math/Mat4f.h"
#include "math/Color.h"

namespace gg { namespace debug {
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float thickness, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float duration, float thickness, const math::Color& color = math::Color::white);
}/*namespace debug*/ } // namespace gg

#endif
