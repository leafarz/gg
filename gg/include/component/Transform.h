#ifndef		GG_TRANSFORM_H
#define		GG_TRANSFORM_H
#pragma once

#include "core/Types.h"
#include "component/Component.h"
#include "math/Vec3f.h"
#include "math/Quaternion.h"
#include "math/Mat4f.h"
namespace gg
{
	class Transform : public Component
	{
	private:
		enum DirtyBits : ubyte
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

		const Math::Vec3f& getPos(void) const;
		Math::Vec3f& setPosX(float x);
		Math::Vec3f& setPosY(float y);
		Math::Vec3f& setPosZ(float z);
		Math::Vec3f& setPos(float x, float y, float z);
		Math::Vec3f& setPos(Math::Vec3f pos);

		const Math::Vec3f& getEuler(void) const;
		Math::Vec3f& setEulerX(float x);
		Math::Vec3f& setEulerY(float y);
		Math::Vec3f& setEulerZ(float z);
		Math::Vec3f& setEuler(float x, float y, float z);
		Math::Vec3f& setEuler(Math::Vec3f euler);

		const Math::Quaternion& getRotation(void) const;
		Math::Quaternion& setRotation(float x, float y, float z, float w);
		Math::Quaternion& setRotation(const Math::Vec3f& axis, float deg);
		Math::Quaternion& lookAt(const Math::Vec3f& forward, const Math::Vec3f& up = Math::Vec3f::up);

		const Math::Vec3f& getScale(void) const;
		Math::Vec3f& setScaleX(float x);
		Math::Vec3f& setScaleY(float y);
		Math::Vec3f& setScaleZ(float z);
		Math::Vec3f& setScale(float x, float y, float z);
		Math::Vec3f& setScale(Math::Vec3f euler);

		const Math::Mat4f& getTransformationMatrix(void);

		bool isDirty(void) const;

	private:
		void setDirty(DirtyBits bit);
		void clearDirty(DirtyBits bit);
		bool isDirty(DirtyBits bit) const;

	private:
		DirtyBits m_DirtyBits = static_cast<DirtyBits>(DirtyBits::Position | DirtyBits::Euler | DirtyBits::Rotation | DirtyBits::Scale);

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
