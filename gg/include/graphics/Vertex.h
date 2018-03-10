#ifndef		GG_VERTEX_H
#define		GG_VERTEX_H
#pragma once

#include "math/Color.h"
#include "math/Vec2f.h"
#include "math/Vec3f.h"

namespace gg { namespace graphics {
	struct Vertex
	{
		Vertex(void);
		Vertex(const Math::Vec3f& position);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord);
		Vertex(const Math::Vec3f& position, const Math::Vec3f& normal);
		Vertex(const Math::Vec3f& position, const Math::Color& color);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Vec3f& normal);
		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Color& color);
		Vertex(const Math::Vec3f& position, const Math::Vec3f& normal, const Math::Color& color);

		Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Vec3f& normal, const Math::Color& color);

		Math::Vec3f position;
		Math::Vec2f texCoord;
		Math::Vec3f normal;
		Math::Color color;

	};// struct Vertex
}/*namespace graphics*/ } // namespace gg

#endif
