#ifndef		GG_VERTEX_H
#define		GG_VERTEX_H
#pragma once

#include "graphics/Color.h"

#include "math/Vec2f.h"
#include "math/Vec3f.h"

namespace gg { namespace graphics {
	struct Vertex
	{
		Vertex(void);
		Vertex(const Math::Vec3f& position);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord);
		Vertex(const Math::Vec3f& position, const Math::Vec3f& normal);
		Vertex(const Math::Vec3f& position, const Color& color);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Vec3f& normal);
		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Color& color);
		Vertex(const Math::Vec3f& position, const Math::Vec3f& normal, const Color& color);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Vec3f& normal, const Color& color);

		Math::Vec3f position;
		Math::Vec2f texCoord;
		Math::Vec3f normal;
		Color color;

	};// struct Vertex
}/*namespace graphics*/ } // namespace gg

#endif
