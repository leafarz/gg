#include "component/Transform.h"

namespace gg
{
	Transform::Transform(void)
	{}

	Transform::~Transform(void)
	{}

	// Position
	const Math::Vec3f& Transform::getPos(void) const
	{
		return m_Position;
	}
	Math::Vec3f& Transform::setPosX(float x) { setDirty(DirtyBits::Position); return m_Position.setX(x); }
	Math::Vec3f& Transform::setPosY(float y) { setDirty(DirtyBits::Position); return m_Position.setY(y); }
	Math::Vec3f& Transform::setPosZ(float z) { setDirty(DirtyBits::Position); return m_Position.setZ(z); }
	Math::Vec3f& Transform::setPos(float x, float y, float z) { setDirty(DirtyBits::Position); return m_Position.set(x, y, z); }
	Math::Vec3f& Transform::setPos(Math::Vec3f pos) { setDirty(DirtyBits::Position); return m_Position.set(pos); }

	// Euler
	const Math::Vec3f& Transform::getEuler(void) const
	{
		return m_Euler;
	}
	Math::Vec3f& Transform::setEulerX(float x)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setX(x);
		m_Rotation = Math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	Math::Vec3f& Transform::setEulerY(float y)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setY(y);
		m_Rotation = Math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	Math::Vec3f& Transform::setEulerZ(float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setZ(z);
		m_Rotation = Math::Quaternion::fromEulerd(m_Euler);


		return m_Euler;
	}
	Math::Vec3f& Transform::setEuler(float x, float y, float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(x, y, z);
		m_Rotation = Math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	Math::Vec3f& Transform::setEuler(Math::Vec3f euler)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(euler);
		m_Rotation = Math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}


	// Rotation
	const Math::Quaternion& Transform::getRotation(void) const
	{
		return m_Rotation;
	}

	Math::Quaternion& Transform::setRotation(float x, float y, float z, float w)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation.set(x, y, z, w);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	Math::Quaternion& Transform::setRotation(const Math::Vec3f& axis, float deg)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation.set(axis, deg);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	Math::Quaternion& Transform::lookAt(const Math::Vec3f& forward, const Math::Vec3f& up)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation = Math::Quaternion::lookRotation(forward, up);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	// Scale
	const Math::Vec3f& Transform::getScale(void) const
	{
		return m_Scale;
	}
	Math::Vec3f& Transform::setScaleX(float x) { setDirty(DirtyBits::Scale); return m_Scale.setX(x); }
	Math::Vec3f& Transform::setScaleY(float y) { setDirty(DirtyBits::Scale); return m_Scale.setY(y); }
	Math::Vec3f& Transform::setScaleZ(float z) { setDirty(DirtyBits::Scale); return m_Scale.setZ(z); }
	Math::Vec3f& Transform::setScale(float x, float y, float z) { setDirty(DirtyBits::Scale); return m_Scale.set(x, y, z); }
	Math::Vec3f& Transform::setScale(Math::Vec3f scale) { setDirty(DirtyBits::Scale); return m_Scale.set(scale); }

	const Math::Mat4f& Transform::getTransformationMatrix(void) const
	{
		return Math::Mat4f();
	}

	void Transform::setDirty(DirtyBits bit)			{ m_DirtyBits = static_cast<DirtyBits>(m_DirtyBits | bit); }
	void Transform::clearDirty(DirtyBits bit)		{ m_DirtyBits = static_cast<DirtyBits>(m_DirtyBits & ~bit); }
	bool Transform::isDirty(DirtyBits bit) const	{ return m_DirtyBits&bit == bit; }
} // namespace gg
