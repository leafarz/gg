#ifndef		GG_FREECAMERA_H
#define		GG_FREECAMERA_H
#pragma once

#include "entity/GameObject.h"
#include "math/Vec2f.h"

namespace gg
{
	class Camera;
	class FreeCamera : public GameObject
	{
	public:
		FreeCamera(void);
		FreeCamera(float fovDeg, float aspectRatio, float zNear, float zFar);
		~FreeCamera(void);

		Camera* getCamera(void);

		void setMoveSpeed(float moveSpeed);

		void onInit(void) override;
		void onUpdate(void) override;

	private:
		Camera* m_Camera;
		math::Vec2f m_PrevMousePos;

		float m_MoveSpeed = 0.1f;
		float m_Sensitivity = 0.05f;
		math::Vec2f m_SensitivityBounds = math::Vec2f(0.001f, 0.1f);

		bool m_IsCursorVisible = false;
	}; // class FreeCamera
} // namespace gg

#endif
