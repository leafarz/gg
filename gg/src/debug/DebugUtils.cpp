#include "debug/DebugUtils.h"

#include "core/Application.h"
#include "core/Scene.h"
#include "graphics/Renderer.h"

namespace gg { namespace debug {
	void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color, float thickness)
	{
		Application::getInstance()->getActiveScene()->getRenderer()->drawLine(from, to, color, thickness);
	}
}/*namespace debug*/ } // namespace gg