#ifndef		GG_DEBUGLINE_H
#define		GG_DEBUGLINE_H
#pragma once

#include "graphics/drawables/Drawable.h"

#include "math/Color.h"
#include "math/Mat4f.h"
#include "math/Vec3f.h"

namespace gg { namespace graphics {
	class Shader;
	class DebugLine : public Drawable
	{
	public:
		struct LineData
		{
			math::Vec3f position;
			math::Color color;
			LineData(const math::Vec3f& position, const math::Color& color)
				: position(position), color(color)
			{ }
		};
	public:
		DebugLine(void);
		~DebugLine(void);

		void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, float thickness);
		void drawLines(const std::vector<LineData>& lineQueue, uint thickness, uint count);
	}; // class DebugLine
}/*namespace debug*/ } // namespace gg

#endif
