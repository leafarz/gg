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
		Vertex(const math::Vec3f& position);

		Vertex(const math::Vec3f& position, const math::Vec2f& texCoord);
		Vertex(const math::Vec3f& position, const math::Vec3f& normal);
		Vertex(const math::Vec3f& position, const math::Color& color);

		Vertex(const math::Vec3f& position, const math::Vec2f& texCoord, const math::Vec3f& normal);
		Vertex(const math::Vec3f& position, const math::Vec2f& texCoord, const math::Color& color);
		Vertex(const math::Vec3f& position, const math::Vec3f& normal, const math::Color& color);

		Vertex(const math::Vec3f& position, const math::Vec2f& texCoord, const math::Vec3f& normal, const math::Color& color);

		math::Vec3f position;
		math::Vec2f texCoord;
		math::Vec3f normal;
		math::Color color;

	};// struct Vertex
}/*namespace graphics*/ } // namespace gg

#endif
