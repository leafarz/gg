#ifndef		GG_TRANSFORM_H
#define		GG_TRANSFORM_H
#pragma once

#include "core/Types.h"
#include "component/Component.h"

#include "math/Mat4f.h"
#include "math/Quaternion.h"
#include "math/Vec3f.h"
namespace gg
{
	class Transform : public Component
	{
	private:
		friend class Renderer;

	private:
		enum class DirtyBits : ubyte
		{
			Position	= 1 << 0,
			Euler		= 1 << 1,
			Rotation	= 1 << 2,
			Scale		= 1 << 3
		};
	public:
		Transform(void);
		~Transform(void);

		static ComponentType getStaticType(void) { return ComponentType::Transform; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		Math::Vec3f getForward(void) const;
		Math::Vec3f getRight(void) const;
		Math::Vec3f getUp(void) const;

		const Math::Vec3f& getPosition(void) const;
		Math::Vec3f& setPositionX(float x);
		Math::Vec3f& setPositionY(float y);
		Math::Vec3f& setPositionZ(float z);
		Math::Vec3f& setPosition(float x, float y, float z);
		Math::Vec3f& setPosition(Math::Vec3f pos);

		Math::Vec3f& addPositionX(float x);
		Math::Vec3f& addPositionY(float y);
		Math::Vec3f& addPositionZ(float z);
		Math::Vec3f& addPosition(float x, float y, float z);
		Math::Vec3f& addPosition(Math::Vec3f pos);

		const Math::Vec3f& getEuler(void) const;
		Math::Vec3f& setEulerX(float x);
		Math::Vec3f& setEulerY(float y);
		Math::Vec3f& setEulerZ(float z);
		Math::Vec3f& setEuler(float x, float y, float z);
		Math::Vec3f& setEuler(Math::Vec3f euler);

		Math::Vec3f& addEulerX(float x);
		Math::Vec3f& addEulerY(float y);
		Math::Vec3f& addEulerZ(float z);
		Math::Vec3f& addEuler(float x, float y, float z);
		Math::Vec3f& addEuler(Math::Vec3f euler);

		const Math::Quaternion& getRotation(void) const;
		Math::Quaternion& setRotation(float x, float y, float z, float w);
		Math::Quaternion& setRotation(const Math::Vec3f& axis, float deg);
		Math::Quaternion& lookAt(const Math::Vec3f& forward, const Math::Vec3f& up = Math::Vec3f::up);

		const Math::Vec3f& getScale(void) const;
		Math::Vec3f& setScaleX(float x);
		Math::Vec3f& setScaleY(float y);
		Math::Vec3f& setScaleZ(float z);
		Math::Vec3f& setScale(float x, float y, float z);
		Math::Vec3f& setScale(Math::Vec3f scale);

		Math::Vec3f& addScaleX(float x);
		Math::Vec3f& addScaleY(float y);
		Math::Vec3f& addScaleZ(float z);
		Math::Vec3f& addScale(float x, float y, float z);
		Math::Vec3f& addScale(Math::Vec3f scale);

		const Math::Mat4f& getTransformationMatrix(void);

		bool isDirty(void) const;

	private:
		void setDirty(DirtyBits bit);
		void clearDirty(void);
		void clearDirty(DirtyBits bit);
		bool isDirty(DirtyBits bit) const;

	private:
		DirtyBits m_DirtyBits = static_cast<DirtyBits>(
			(ubyte)DirtyBits::Position |
			(ubyte)DirtyBits::Euler |
			(ubyte)DirtyBits::Rotation |
			(ubyte)DirtyBits::Scale
		);

		// TODO: check if all of these are necessary
		Math::Vec3f m_Position;
		Math::Vec3f m_Euler;
		Math::Quaternion m_Rotation;
		Math::Vec3f m_Scale;

		Math::Mat4f m_TransformationMatrix;
		Math::Mat4f m_RotMatrix;
	}; // class Transform
} // namespace gg

#endif
