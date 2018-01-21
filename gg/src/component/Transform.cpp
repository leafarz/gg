#include "component/Transform.h"

namespace gg
{
	Transform::Transform(void)
	{}

	Transform::~Transform(void)
	{}

	Math::Vec3f& Transform::setPosX(float x) { return m_Position.setX(x); }
	Math::Vec3f& Transform::setPosY(float y) { return m_Position.setY(y); }
	Math::Vec3f& Transform::setPosZ(float z) { return m_Position.setZ(z); }
	Math::Vec3f& Transform::setPos(float x, float y, float z) { return m_Position.set(x, y, z); }
	Math::Vec3f& Transform::setPos(Math::Vec3f pos) { return m_Position.set(pos); }
} // namespace gg
