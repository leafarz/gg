#ifndef		GG_DEBUGUTILS_H
#define		GG_DEBUGUTILS_H
#pragma once

#include "core/Types.h"

#include "math/Color.h"
#include "math/Mat4f.h"
#include "math/Quaternion.h"


namespace gg { namespace debug {
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float thickness, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, float thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, float thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, float thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, float thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, float thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, float thickness, float duration, const math::Color& color = math::Color::white);
}/*namespace debug*/ } // namespace gg

#endif
