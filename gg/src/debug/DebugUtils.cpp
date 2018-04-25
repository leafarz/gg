#include "debug/DebugUtils.h"

#include "core/Application.h"
#include "core/Scene.h"
#include "graphics/Renderer.h"

namespace gg { namespace debug {
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, 1);
	}
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float thickness, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness);
	}
	void drawLine(const math::Vec3f& from, const math::Vec3f& to, float thickness, float duration, const math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness, duration);
	}
}/*namespace debug*/ } // namespace gg