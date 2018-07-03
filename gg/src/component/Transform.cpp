#include "component/Transform.h"

namespace gg
{
	Transform::Transform(void)
		: m_Position(math::Vec3f(0,0,0)), m_Euler(math::Vec3f(0, 0, 0)), m_Rotation(math::Quaternion(0, 0, 0, 1)), m_Scale(math::Vec3f(1, 1, 1))
	{}

	Transform::~Transform(void)
	{}

	math::Vec3f Transform::getForward(void) const	{ return m_Rotation.getForward(); }
	math::Vec3f Transform::getRight(void) const		{ return m_Rotation.getRight(); }
	math::Vec3f Transform::getUp(void) const		{ return m_Rotation.getUp(); }

	// Position
	math::Vec3f& Transform::setPositionX(float x) { setDirty(DirtyBits::Position); return m_Position.setX(x); }
	math::Vec3f& Transform::setPositionY(float y) { setDirty(DirtyBits::Position); return m_Position.setY(y); }
	math::Vec3f& Transform::setPositionZ(float z) { setDirty(DirtyBits::Position); return m_Position.setZ(z); }
	math::Vec3f& Transform::setPosition(float x, float y, float z) { setDirty(DirtyBits::Position); return m_Position.set(x, y, z); }
	math::Vec3f& Transform::setPosition(math::Vec3f pos) { setDirty(DirtyBits::Position); return m_Position.set(pos); }

	math::Vec3f& Transform::addPositionX(float x) { setDirty(DirtyBits::Position); return m_Position.setX(m_Position.x + x); }
	math::Vec3f& Transform::addPositionY(float y) { setDirty(DirtyBits::Position); return m_Position.setY(m_Position.y + y); }
	math::Vec3f& Transform::addPositionZ(float z) { setDirty(DirtyBits::Position); return m_Position.setZ(m_Position.z + z); }
	math::Vec3f& Transform::addPosition(float x, float y, float z)
	{
		setDirty(DirtyBits::Position);
		return m_Position.set( m_Position.x + x, m_Position.y + y, m_Position.z + z );
	}

	math::Vec3f& Transform::addPosition(math::Vec3f pos)
	{
		setDirty(DirtyBits::Position);
		return m_Position.set(m_Position + pos);
	}

	// Euler
	math::Vec3f& Transform::setEulerX(float x)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setX(x);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	math::Vec3f& Transform::setEulerY(float y)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setY(y);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	math::Vec3f& Transform::setEulerZ(float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setZ(z);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);


		return m_Euler;
	}
	math::Vec3f& Transform::setEuler(float x, float y, float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(x, y, z);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}
	math::Vec3f& Transform::setEuler(math::Vec3f euler)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(euler);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}

	math::Vec3f& Transform::addEulerX(float x)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setX(m_Euler.x + x);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}

	math::Vec3f& Transform::addEulerY(float y)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setY(m_Euler.y + y);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}

	math::Vec3f& Transform::addEulerZ(float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.setZ(m_Euler.z + z);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}

	math::Vec3f& Transform::addEuler(float x, float y, float z)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(m_Euler.x + x, m_Euler.y + y, m_Euler.z + z);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}

	math::Vec3f & Transform::addEuler(math::Vec3f euler)
	{
		setDirty(DirtyBits::Rotation);
		m_Euler.set(m_Euler + euler);
		m_Rotation = math::Quaternion::fromEulerd(m_Euler);

		return m_Euler;
	}


	// Rotation
	math::Quaternion& Transform::setRotation(float x, float y, float z, float w)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation.set(x, y, z, w);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	math::Quaternion& Transform::setRotation(const math::Vec3f& axis, float deg)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation.set(axis, deg);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	math::Quaternion& Transform::lookAt(const math::Vec3f& forward, const math::Vec3f& up)
	{
		setDirty(DirtyBits::Rotation);
		m_Rotation = math::Quaternion::lookRotation(forward);
		m_Euler = m_Rotation.toEulerd();

		return m_Rotation;
	}

	// Scale
	math::Vec3f& Transform::setScaleX(float x) { setDirty(DirtyBits::Scale); return m_Scale.setX(x); }
	math::Vec3f& Transform::setScaleY(float y) { setDirty(DirtyBits::Scale); return m_Scale.setY(y); }
	math::Vec3f& Transform::setScaleZ(float z) { setDirty(DirtyBits::Scale); return m_Scale.setZ(z); }
	math::Vec3f& Transform::setScale(float x, float y, float z) { setDirty(DirtyBits::Scale); return m_Scale.set(x, y, z); }
	math::Vec3f& Transform::setScale(math::Vec3f scale) { setDirty(DirtyBits::Scale); return m_Scale.set(scale); }

	math::Vec3f & Transform::addScaleX(float x) { setDirty(DirtyBits::Scale); return m_Scale.setX(m_Scale.x + x); }
	math::Vec3f & Transform::addScaleY(float y) { setDirty(DirtyBits::Scale); return m_Scale.setY(m_Scale.y + y); }
	math::Vec3f & Transform::addScaleZ(float z) { setDirty(DirtyBits::Scale); return m_Scale.setZ(m_Scale.z + z); }
	math::Vec3f & Transform::addScale(float x, float y, float z)
	{
		setDirty(DirtyBits::Scale);
		return m_Scale.set( m_Scale.x + x, m_Scale.y + y, m_Scale.z + z );
	}
	math::Vec3f & Transform::addScale(math::Vec3f scale){ setDirty(DirtyBits::Scale); return m_Scale.set(m_Scale + scale); }


	const math::Mat4f& Transform::getTransformationMatrix(void)
	{
		bool _posBit = isDirty(DirtyBits::Position);
		bool _rotBit = isDirty(static_cast<DirtyBits>((ubyte)DirtyBits::Euler| (ubyte)DirtyBits::Rotation));
		bool _scaleBit = isDirty(DirtyBits::Scale);
		
		if (_rotBit) { m_RotMatrix = math::Mat4f::rotationMatrix(m_Rotation); }

		if (_posBit | _rotBit | _scaleBit)
		{
			// translation * rotation
			float _m00 = m_Scale.x * (m_RotMatrix[0] + m_Position.x * m_RotMatrix[12]);
			float _m10 = m_Scale.x * (m_RotMatrix[4] + m_Position.y * m_RotMatrix[12]);
			float _m20 = m_Scale.x * (m_RotMatrix[8] + m_Position.z * m_RotMatrix[12]);
			float _m30 = m_Scale.x * m_RotMatrix[12];

			float _m01 = m_Scale.y * (m_RotMatrix[1] + m_Position.x * m_RotMatrix[13]);
			float _m11 = m_Scale.y * (m_RotMatrix[5] + m_Position.y * m_RotMatrix[13]);
			float _m21 = m_Scale.y * (m_RotMatrix[9] + m_Position.z * m_RotMatrix[13]);
			float _m31 = m_Scale.y * m_RotMatrix[13];

			float _m02 = m_Scale.z * (m_RotMatrix[2] + m_Position.x * m_RotMatrix[14]);
			float _m12 = m_Scale.z * (m_RotMatrix[6] + m_Position.y * m_RotMatrix[14]);
			float _m22 = m_Scale.z * (m_RotMatrix[10] + m_Position.z * m_RotMatrix[14]);
			float _m32 = m_Scale.z * m_RotMatrix[14];

			float _m03 = m_RotMatrix[3] + m_Position.x * m_RotMatrix[15];
			float _m13 = m_RotMatrix[7] + m_Position.y * m_RotMatrix[15];
			float _m23 = m_RotMatrix[11] + m_Position.z * m_RotMatrix[15];
			float _m33 = m_RotMatrix[15];

			m_TransformationMatrix = math::Mat4f(
				_m00, _m01, _m02, _m03,
				_m10, _m11, _m12, _m13,
				_m20, _m21, _m22, _m23,
				_m30, _m31, _m32, _m33
			);
		}
		return m_TransformationMatrix;
	}

	bool Transform::isDirty(void) const
	{
		return isDirty(static_cast<DirtyBits>((ubyte)DirtyBits::Position | (ubyte)DirtyBits::Euler | (ubyte)DirtyBits::Rotation | (ubyte)DirtyBits::Scale));
	}

	void Transform::setDirty(DirtyBits bit)			{ m_DirtyBits = static_cast<DirtyBits>((ubyte)m_DirtyBits | (ubyte)bit); }
	void Transform::clearDirty(void)				{ m_DirtyBits = static_cast<DirtyBits>(0); }
	void Transform::clearDirty(DirtyBits bit)		{ m_DirtyBits = static_cast<DirtyBits>((ubyte)m_DirtyBits & ~(ubyte)bit); }
	bool Transform::isDirty(DirtyBits bit) const	{ return ((ubyte)m_DirtyBits&(ubyte)bit) != 0; }
} // namespace gg
