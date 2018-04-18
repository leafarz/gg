#ifndef		GG_CAMERA_H
#define		GG_CAMERA_H
#pragma once

#include "component/Component.h"

#include "core/Types.h"
#include "math/Mat4f.h"

namespace gg
{
	class Camera : public Component
	{
	public:
		Camera(void);
		Camera(float fovDeg, float aspectRatio, float zNear, float zFar);
		~Camera(void);

		static ComponentType getStaticType(void) { return ComponentType::Camera; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setPerspective(float fovDeg, float aspectRatio, float zNear, float zFar);
		void setOrthographic(float size, float zNear, float zFar);
		void setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);

		const Math::Mat4f& getProjectionMatrix(void) const;
		const Math::Mat4f& getViewMatrix(void);
		const Math::Mat4f getViewProjectionMatrix(void);

		void update(void);

	private:
		Math::Mat4f m_ProjectionMatrix;
		Math::Mat4f m_ViewMatrix;

	}; // class Camera
} // namespace gg

#endif
