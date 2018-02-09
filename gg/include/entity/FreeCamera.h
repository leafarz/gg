#ifndef		GG_FREECAMERA_H
#define		GG_FREECAMERA_H
#pragma once

#include "entity/GameObject.h"

namespace gg
{
	class FreeCamera : public GameObject
	{
	public:
		FreeCamera(void);
		FreeCamera(float fovDeg, float aspectRatio, float zNear, float zFar);
		~FreeCamera(void);

		Camera* getCamera(void);

	private:
		Camera* m_Camera;
	}; // class FreeCamera
} // namespace gg

#endif
