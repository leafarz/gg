#include "entity/FreeCamera.h"

#include "component/Camera.h"
namespace gg
{
	FreeCamera::FreeCamera(void)
	{
		m_Camera = addComponent<Camera>();
	}

	FreeCamera::FreeCamera(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		m_Camera = addComponent<Camera>();
		m_Camera->setPerspectiveCamera(fovDeg, aspectRatio, zNear, zFar);
	}

	FreeCamera::~FreeCamera(void)
	{
		// TODO: remove component or delete?
	}

	Camera * FreeCamera::getCamera(void)
	{
		return m_Camera;
	}
} // namespace gg
