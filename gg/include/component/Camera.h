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
	private:
		friend class Scene;

	public:
		Camera(void);
		Camera(float fovDeg, float aspectRatio, float zNear, float zFar);
		~Camera(void);

		static ComponentType getStaticType(void) { return ComponentType::Camera; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		inline float getNearClipPlane(void) const { return m_NearClipPlane; }
		inline float getFarClipPlane(void) const { return m_FarClipPlane; }

		inline float getFOV(void) const { return m_FOV; }
		inline float getAspectRatio(void) const { return m_AspectRatio; }

		inline float getLeft(void) const { return m_Left; }
		inline float getRight(void) const { return m_Right; }
		inline float getBottom(void) const { return m_Bottom; }
		inline float getTop(void) const { return m_Top; }

		void setPerspective(float fovDeg, float aspectRatio, float zNear, float zFar);
		void setOrthographic(float size, float zNear, float zFar);
		void setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);

		const math::Mat4f& getProjectionMatrix(void) const;
		const math::Mat4f& getViewMatrix(void);
		const math::Mat4f& getViewProjectionMatrix(void);

		bool isCameraActive(void);

		void update(void);

		static math::Mat4f viewMatrix(const math::Vec3f& position, const math::Quaternion& rotation);

	private:
		void setIsCameraActive(bool isCameraActive);

	private:
		math::Mat4f m_ProjectionMatrix;
		math::Mat4f m_ViewMatrix;
		math::Mat4f m_ViewProjectionMatrix;

		float m_NearClipPlane;
		float m_FarClipPlane;

		// Perspective
		float m_FOV;
		float m_AspectRatio;

		// Orthographic
		float m_Left;
		float m_Right;
		float m_Bottom;
		float m_Top;

		bool m_IsCameraActive = false;
	}; // class Camera
} // namespace gg

#endif
