#ifndef		GG_DEBUGUTILS_H
#define		GG_DEBUGUTILS_H
#pragma once

#include "core/Types.h"

#include "math/Color.h"
#include "math/Mat4f.h"
#include "math/Quaternion.h"

namespace gg { class Camera; }

namespace gg { namespace debug {
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, uint thickness, const math::Color& color = math::Color::white);
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, uint thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, uint thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, uint thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, uint thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, uint thickness, float duration, const math::Color& color = math::Color::white);

	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, uint thickness, const math::Color& color = math::Color::white);
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, uint thickness, float duration, const math::Color& color = math::Color::white);

	void drawCameraFrustum(Camera* camera);
	void drawCameraFrustum(const math::Vec3f& position, const math::Quaternion& rotation, float fovDeg, float aspectRatio, float zNear, float zFar);
}/*namespace debug*/ } // namespace gg

#endif
