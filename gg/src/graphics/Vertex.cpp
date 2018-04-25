#include "graphics/Vertex.h"

namespace gg { namespace graphics {
	Vertex::Vertex(void)
	{ }
	Vertex::Vertex(const math::Vec3f& position)
		: position(position)
	{ }
	Vertex::Vertex(const math::Vec3f& position, const math::Vec2f& texCoord)
		: position(position), texCoord(texCoord)
	{ }
	Vertex::Vertex(const math::Vec3f & position, const math::Vec3f & normal)
		: position(position), normal(normal)
	{ }
	Vertex::Vertex(const math::Vec3f & position, const math::Color & color)
		: position(position), color(color)
	{ }
	Vertex::Vertex(const math::Vec3f& position, const math::Vec2f& texCoord, const math::Vec3f& normal)
		: position(position), texCoord(texCoord), normal(normal)
	{ }
	Vertex::Vertex(const math::Vec3f & position, const math::Vec2f & texCoord, const math::Color & color)
		: position(position), texCoord(texCoord), color(color)
	{ }
	Vertex::Vertex(const math::Vec3f & position, const math::Vec3f & normal, const math::Color & color)
		: position(position), normal(normal), color(color)
	{ }
	Vertex::Vertex(const math::Vec3f & position, const math::Vec2f & texCoord, const math::Vec3f & normal, const math::Color & color)
		: position(position), texCoord(texCoord), normal(normal), color(color)
	{ }
}/*namespace graphics*/
} // namespace gg
