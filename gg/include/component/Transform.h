#ifndef		GG_TRANSFORM_H
#define		GG_TRANSFORM_H
#pragma once

#include "core/Types.h"
#include "component/Component.h"

#include "math/Mat4f.h"
#include "math/Quaternion.h"
#include "math/Vec3f.h"

namespace gg { namespace graphics { class Renderer; } }

namespace gg
{
	class Transform : public Component
	{
	private:
		friend class graphics::Renderer;

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

		math::Vec3f getForward(void) const;
		math::Vec3f getRight(void) const;
		math::Vec3f getUp(void) const;

		const math::Vec3f& getPosition(void) const;
		math::Vec3f& setPositionX(float x);
		math::Vec3f& setPositionY(float y);
		math::Vec3f& setPositionZ(float z);
		math::Vec3f& setPosition(float x, float y, float z);
		math::Vec3f& setPosition(math::Vec3f pos);

		math::Vec3f& addPositionX(float x);
		math::Vec3f& addPositionY(float y);
		math::Vec3f& addPositionZ(float z);
		math::Vec3f& addPosition(float x, float y, float z);
		math::Vec3f& addPosition(math::Vec3f pos);

		const math::Vec3f& getEuler(void) const;
		math::Vec3f& setEulerX(float x);
		math::Vec3f& setEulerY(float y);
		math::Vec3f& setEulerZ(float z);
		math::Vec3f& setEuler(float x, float y, float z);
		math::Vec3f& setEuler(math::Vec3f euler);

		math::Vec3f& addEulerX(float x);
		math::Vec3f& addEulerY(float y);
		math::Vec3f& addEulerZ(float z);
		math::Vec3f& addEuler(float x, float y, float z);
		math::Vec3f& addEuler(math::Vec3f euler);

		const math::Quaternion& getRotation(void) const;
		math::Quaternion& setRotation(float x, float y, float z, float w);
		math::Quaternion& setRotation(const math::Vec3f& axis, float deg);
		math::Quaternion& lookAt(const math::Vec3f& forward, const math::Vec3f& up = math::Vec3f::up);

		const math::Vec3f& getScale(void) const;
		math::Vec3f& setScaleX(float x);
		math::Vec3f& setScaleY(float y);
		math::Vec3f& setScaleZ(float z);
		math::Vec3f& setScale(float x, float y, float z);
		math::Vec3f& setScale(math::Vec3f scale);

		math::Vec3f& addScaleX(float x);
		math::Vec3f& addScaleY(float y);
		math::Vec3f& addScaleZ(float z);
		math::Vec3f& addScale(float x, float y, float z);
		math::Vec3f& addScale(math::Vec3f scale);

		const math::Mat4f& getTransformationMatrix(void);

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
		math::Vec3f m_Position;
		math::Vec3f m_Euler;
		math::Quaternion m_Rotation;
		math::Vec3f m_Scale;

		math::Mat4f m_TransformationMatrix;
		math::Mat4f m_RotMatrix;
	}; // class Transform
} // namespace gg

#endif
