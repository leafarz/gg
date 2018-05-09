#include "debug/DebugUtils.h"

#include "core/Application.h"
#include "core/Scene.h"

#include "graphics/Renderer.h"

namespace gg { namespace debug {
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, 1);
	}
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, uint thickness, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness);
	}
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, uint thickness, float duration, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness, duration);
	}

	void drawWireCube(const math::Vec3f& origin, float size, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, color);
		drawLine(_p0, _p3, color);
		drawLine(_p2, _p1, color);
		drawLine(_p2, _p3, color);

		// back
		drawLine(_p4, _p5, color);
		drawLine(_p4, _p7, color);
		drawLine(_p6, _p5, color);
		drawLine(_p6, _p7, color);

		// left
		drawLine(_p0, _p4, color);
		drawLine(_p1, _p5, color);

		// right
		drawLine(_p3, _p7, color);
		drawLine(_p2, _p6, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, uint thickness, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, color);
		drawLine(_p0, _p3, thickness, color);
		drawLine(_p2, _p1, thickness, color);
		drawLine(_p2, _p3, thickness, color);

		// back
		drawLine(_p4, _p5, thickness, color);
		drawLine(_p4, _p7, thickness, color);
		drawLine(_p6, _p5, thickness, color);
		drawLine(_p6, _p7, thickness, color);

		// left
		drawLine(_p0, _p4, thickness, color);
		drawLine(_p1, _p5, thickness, color);

		// right
		drawLine(_p3, _p7, thickness, color);
		drawLine(_p2, _p6, thickness, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, uint thickness, float duration, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, duration, color);
		drawLine(_p0, _p3, thickness, duration, color);
		drawLine(_p2, _p1, thickness, duration, color);
		drawLine(_p2, _p3, thickness, duration, color);

		// back
		drawLine(_p4, _p5, thickness, duration, color);
		drawLine(_p4, _p7, thickness, duration, color);
		drawLine(_p6, _p5, thickness, duration, color);
		drawLine(_p6, _p7, thickness, duration, color);

		// left
		drawLine(_p0, _p4, thickness, duration, color);
		drawLine(_p1, _p5, thickness, duration, color);

		// right
		drawLine(_p3, _p7, thickness, duration, color);
		drawLine(_p2, _p6, thickness, duration, color);
	}

	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Quaternion _rot = math::Quaternion(euler);
		math::Vec3f _p0 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + _rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + _rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + _rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + _rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, color);
		drawLine(_p0, _p3, color);
		drawLine(_p2, _p1, color);
		drawLine(_p2, _p3, color);

		// back
		drawLine(_p4, _p5, color);
		drawLine(_p4, _p7, color);
		drawLine(_p6, _p5, color);
		drawLine(_p6, _p7, color);

		// left
		drawLine(_p0, _p4, color);
		drawLine(_p1, _p5, color);

		// right
		drawLine(_p3, _p7, color);
		drawLine(_p2, _p6, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, uint thickness, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Quaternion _rot = math::Quaternion(euler);
		math::Vec3f _p0 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + _rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + _rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + _rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + _rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, color);
		drawLine(_p0, _p3, thickness, color);
		drawLine(_p2, _p1, thickness, color);
		drawLine(_p2, _p3, thickness, color);

		// back
		drawLine(_p4, _p5, thickness, color);
		drawLine(_p4, _p7, thickness, color);
		drawLine(_p6, _p5, thickness, color);
		drawLine(_p6, _p7, thickness, color);

		// left
		drawLine(_p0, _p4, thickness, color);
		drawLine(_p1, _p5, thickness, color);

		// right
		drawLine(_p3, _p7, thickness, color);
		drawLine(_p2, _p6, thickness, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, const math::Vec3f& euler, uint thickness, float duration, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Quaternion _rot = math::Quaternion(euler);
		math::Vec3f _p0 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + _rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + _rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + _rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + _rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + _rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + _rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, color);
		drawLine(_p0, _p3, thickness, color);
		drawLine(_p2, _p1, thickness, color);
		drawLine(_p2, _p3, thickness, color);

		// back
		drawLine(_p4, _p5, thickness, color);
		drawLine(_p4, _p7, thickness, color);
		drawLine(_p6, _p5, thickness, color);
		drawLine(_p6, _p7, thickness, color);

		// left
		drawLine(_p0, _p4, thickness, color);
		drawLine(_p1, _p5, thickness, color);

		// right
		drawLine(_p3, _p7, thickness, color);
		drawLine(_p2, _p6, thickness, color);
	}

	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, color);
		drawLine(_p0, _p3, color);
		drawLine(_p2, _p1, color);
		drawLine(_p2, _p3, color);

		// back
		drawLine(_p4, _p5, color);
		drawLine(_p4, _p7, color);
		drawLine(_p6, _p5, color);
		drawLine(_p6, _p7, color);

		// left
		drawLine(_p0, _p4, color);
		drawLine(_p1, _p5, color);

		// right
		drawLine(_p3, _p7, color);
		drawLine(_p2, _p6, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, uint thickness, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, color);
		drawLine(_p0, _p3, thickness, color);
		drawLine(_p2, _p1, thickness, color);
		drawLine(_p2, _p3, thickness, color);

		// back
		drawLine(_p4, _p5, thickness, color);
		drawLine(_p4, _p7, thickness, color);
		drawLine(_p6, _p5, thickness, color);
		drawLine(_p6, _p7, thickness, color);

		// left
		drawLine(_p0, _p4, thickness, color);
		drawLine(_p1, _p5, thickness, color);

		// right
		drawLine(_p3, _p7, thickness, color);
		drawLine(_p2, _p6, thickness, color);
	}
	void drawWireCube(const math::Vec3f& origin, float size, const math::Quaternion& rot, uint thickness, float duration, const math::Color& color)
	{
		float _halfSize = size * 0.5f;

		math::Vec3f _p0 = origin + rot * math::Vec3f(-_halfSize, -_halfSize, -_halfSize);	// lower left	-z
		math::Vec3f _p1 = origin + rot * math::Vec3f(-_halfSize,  _halfSize, -_halfSize);	// upper left	-z
		math::Vec3f _p2 = origin + rot * math::Vec3f( _halfSize,  _halfSize, -_halfSize);	// upper right	-z
		math::Vec3f _p3 = origin + rot * math::Vec3f( _halfSize, -_halfSize, -_halfSize);	// lower right	-z
		math::Vec3f _p4 = origin + rot * math::Vec3f(-_halfSize, -_halfSize,  _halfSize);	// lower left	+z
		math::Vec3f _p5 = origin + rot * math::Vec3f(-_halfSize,  _halfSize,  _halfSize);	// upper left	+z
		math::Vec3f _p6 = origin + rot * math::Vec3f( _halfSize,  _halfSize,  _halfSize);	// upper right	+z
		math::Vec3f _p7 = origin + rot * math::Vec3f( _halfSize, -_halfSize,  _halfSize);	// lower right	+z

		// front
		drawLine(_p0, _p1, thickness, color);
		drawLine(_p0, _p3, thickness, color);
		drawLine(_p2, _p1, thickness, color);
		drawLine(_p2, _p3, thickness, color);

		// back
		drawLine(_p4, _p5, thickness, color);
		drawLine(_p4, _p7, thickness, color);
		drawLine(_p6, _p5, thickness, color);
		drawLine(_p6, _p7, thickness, color);

		// left
		drawLine(_p0, _p4, thickness, color);
		drawLine(_p1, _p5, thickness, color);

		// right
		drawLine(_p3, _p7, thickness, color);
		drawLine(_p2, _p6, thickness, color);
	}
}/*namespace debug*/ } // namespace gg