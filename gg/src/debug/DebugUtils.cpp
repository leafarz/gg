#include "debug/DebugUtils.h"

#include "core/Application.h"
#include "core/Scene.h"
#include "graphics/Renderer.h"

namespace gg { namespace debug {
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color);
	}
}/*namespace debug*/ } // namespace gg