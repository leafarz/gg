#ifndef		GG_CAMERA_H
#define		GG_CAMERA_H
#pragma once

#include "component/Component.h"

#include "math/Mat4f.h"
#include "core/Types.h"
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

		void setPerspectiveCamera(float fovDeg, float aspectRatio, float zNear, float zFar);

		const Math::Mat4f& getProjectionMatrix(void) const;
		const Math::Mat4f getViewMatrix(void);
		const Math::Mat4f getViewProjectionMatrix(void);

		void update(void);

	private:
		Math::Mat4f m_ProjectionMatrix;

	}; // class Camera
} // namespace gg

#endif
