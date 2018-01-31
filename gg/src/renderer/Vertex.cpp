#include "renderer/Vertex.h"

namespace gg
{
	Vertex::Vertex(void)
	{ }
	Vertex::Vertex(const Math::Vec3f& position)
		: position(position)
	{ }
	Vertex::Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord)
		: position(position), texCoord(texCoord)
	{ }
	Vertex::Vertex(const Math::Vec3f & position, const Math::Vec3f & normal)
		: position(position), normal(normal)
	{ }
	Vertex::Vertex(const Math::Vec3f & position, const Color & color)
		: position(position), color(color)
	{ }
	Vertex::Vertex(const Math::Vec3f& position, const Math::Vec2f& texCoord, const Math::Vec3f& normal)
		: position(position), texCoord(texCoord), normal(normal)
	{ }
	Vertex::Vertex(const Math::Vec3f & position, const Math::Vec2f & texCoord, const Color & color)
		: position(position), texCoord(texCoord), color(color)
	{ }
	Vertex::Vertex(const Math::Vec3f & position, const Math::Vec3f & normal, const Color & color)
		: position(position), normal(normal), color(color)
	{ }
	Vertex::Vertex(const Math::Vec3f & position, const Math::Vec2f & texCoord, const Math::Vec3f & normal, const Color & color)
		: position(position), texCoord(texCoord), normal(normal), color(color)
	{ }
} // namespace gg
