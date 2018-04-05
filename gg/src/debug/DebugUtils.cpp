#include "debug/DebugUtils.h"

#include "core/Application.h"
#include "core/Scene.h"
#include "graphics/Renderer.h"

namespace gg { namespace debug {
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, 1);
	}
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, float thickness, const Math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness);
	}
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, float thickness, float duration, const Math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness, duration);
	}
}/*namespace debug*/ } // namespace gg