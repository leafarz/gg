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
	private:
		struct LineData
		{
			Math::Vec3f position;
			Math::Color color;
			LineData(const Math::Vec3f& position, const Math::Color& color)
				: position(position), color(color)
			{ }
		};
	public:
		DebugLine(void);
		~DebugLine(void);

		void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color);
	}; // class DebugLine
}/*namespace debug*/ } // namespace gg

#endif
