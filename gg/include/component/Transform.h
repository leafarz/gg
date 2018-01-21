#ifndef		GG_TRANSFORM_H
#define		GG_TRANSFORM_H
#pragma once

#include "component/Component.h"
#include "math/Vec3f.h"
#include "math/Quaternion.h"
#include "math/Mat4f.h"
namespace gg
{
	class Transform : public Component
	{
	public:
		Transform(void);
		~Transform(void);

		static ComponentType getStaticType(void) { return ComponentType::Transform; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		Math::Vec3f& setPosX(float x);
		Math::Vec3f& setPosY(float y);
		Math::Vec3f& setPosZ(float z);
		Math::Vec3f& setPos(float x, float y, float z);
		Math::Vec3f& setPos(Math::Vec3f pos);

		inline const Math::Vec3f& getPos(void) const { return m_Position; };

	private:
		// TODO: check if all of these are necessary
		Math::Vec3f m_Position;
		Math::Vec3f m_Euler;
		Math::Quaternion m_Rotation;
		Math::Vec3f m_Scale;
		Math::Mat4f m_TransformationMatrix;
	}; // class Transform
} // namespace gg

#endif
