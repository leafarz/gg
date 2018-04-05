#ifndef		GG_DEBUGUTILS_H
#define		GG_DEBUGUTILS_H
#pragma once

#include "math/Mat4f.h"
#include "math/Color.h"

namespace gg { namespace debug {
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color = Math::Color::white);
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, float thickness, const Math::Color& color = Math::Color::white);
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, float duration, float thickness, const Math::Color& color = Math::Color::white);
}/*namespace debug*/ } // namespace gg

#endif
