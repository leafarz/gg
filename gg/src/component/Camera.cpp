#include "component/Camera.h"

#include "entity/GameObject.h"
namespace gg
{
	Camera::Camera(float fovDeg, float aspectRatio, float zNear, float zFar)
		: m_ProjectionMatrix(Math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar))
	{ }

	Camera::~Camera(void)
	{ }

	void Camera::setPerspectiveCamera(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		m_ProjectionMatrix = Math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar);
	}

	const Math::Mat4f & Camera::getProjectionMatrix(void) const
	{
		return m_ProjectionMatrix;
	}

	const Math::Mat4f & Camera::getViewProjectionMatrix(void)
	{
		Transform* _t = m_GameObject->getTransform();
		// TODO: insert return statement here
	}

	void Camera::update(void)
	{ }
} // namespace gg
