#include "component/Camera.h"

#include "core/Application.h"
#include "core/Scene.h"

#include "entity/GameObject.h"

#include "graphics/RenderTarget.h"

namespace gg
{
	Camera::Camera(void)
	{ }
	Camera::Camera(float fovDeg, float aspectRatio, float zNear, float zFar)
		: m_FOV(fovDeg), m_AspectRatio(aspectRatio), m_NearClipPlane(zNear), m_FarClipPlane(zFar), m_ProjectionMatrix(math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar))
	{ }

	Camera::~Camera(void)
	{ }

	void Camera::setPerspective(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		m_ProjectionMatrix = math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar);

		m_FOV = fovDeg;
		m_AspectRatio = aspectRatio;

		m_NearClipPlane = zNear;
		m_FarClipPlane = zFar;
	}

	void Camera::setOrthographic(float size, float zNear, float zFar)
	{
		m_ProjectionMatrix = math::Mat4f::orthographicMatrix(-size, size, -size, size, zNear, zFar);

		m_Left = -size;
		m_Right = size;
		m_Bottom = -size;
		m_Top = size;

		m_NearClipPlane = zNear;
		m_FarClipPlane = zFar;
	}

	void Camera::setOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_ProjectionMatrix = math::Mat4f::orthographicMatrix(left, right, bottom, top, zNear, zFar);

		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;

		m_NearClipPlane = zNear;
		m_FarClipPlane = zFar;
	}

	const math::Mat4f& Camera::getProjectionMatrix(void) const
	{
		return m_ProjectionMatrix;
	}

	const math::Mat4f& Camera::getViewMatrix(void)
	{
		const Transform* const _t = m_GameObject->getTransform();

		if (_t->isDirty())
		{
			const math::Vec3f& _pos = _t->getPosition();
			const math::Quaternion& _q = _t->getRotation().conjugate();
			math::Mat4f _rotMatrix = math::Mat4f::rotationMatrix(_q);

			// we use negative position for camera view matrix
			float _m03 = _rotMatrix[3]  - _pos.x*_rotMatrix[0]  - _pos.y*_rotMatrix[1]  - _pos.z*_rotMatrix[2];
			float _m13 = _rotMatrix[7]  - _pos.x*_rotMatrix[4]  - _pos.y*_rotMatrix[5]  - _pos.z*_rotMatrix[6];
			float _m23 = _rotMatrix[11] - _pos.x*_rotMatrix[8]  - _pos.y*_rotMatrix[9]  - _pos.z*_rotMatrix[10];
			float _m33 = _rotMatrix[15] - _pos.x*_rotMatrix[12] - _pos.y*_rotMatrix[13] - _pos.z*_rotMatrix[14];

			m_ViewMatrix.set(
				_rotMatrix[0],  _rotMatrix[1],  _rotMatrix[2],  _m03,
				_rotMatrix[4],  _rotMatrix[5],  _rotMatrix[6],  _m13,
				_rotMatrix[8],  _rotMatrix[9],  _rotMatrix[10], _m23,
				_rotMatrix[12], _rotMatrix[13], _rotMatrix[14], _m33
			);
		}

		return m_ViewMatrix;
	}

	const math::Mat4f& Camera::getViewProjectionMatrix(void)
	{
		const Transform* const _t = m_GameObject->getTransform();

		if (_t->isDirty())
		{
			m_ViewProjectionMatrix = getProjectionMatrix() * getViewMatrix();
		}

		return m_ViewProjectionMatrix;
	}

	math::Mat4f Camera::viewMatrix(const math::Vec3f& position, const math::Quaternion& rotation)
	{
		math::Quaternion _q = rotation.conjugate();
		math::Mat4f _rotMatrix = math::Mat4f::rotationMatrix(_q);

		// we use negative position for camera view matrix
		float _m03 = _rotMatrix[3]  - position.x*_rotMatrix[0]  - position.y*_rotMatrix[1]  - position.z*_rotMatrix[2];
		float _m13 = _rotMatrix[7]  - position.x*_rotMatrix[4]  - position.y*_rotMatrix[5]  - position.z*_rotMatrix[6];
		float _m23 = _rotMatrix[11] - position.x*_rotMatrix[8]  - position.y*_rotMatrix[9]  - position.z*_rotMatrix[10];
		float _m33 = _rotMatrix[15] - position.x*_rotMatrix[12] - position.y*_rotMatrix[13] - position.z*_rotMatrix[14];

		return _rotMatrix.set(3, _m03).set(7, _m13).set(11, _m23).set(15, _m33);
	}

	void Camera::setIsCameraActive(bool isCameraActive)
	{
		m_IsCameraActive = isCameraActive;
	}

	bool Camera::isCameraActive(void)
	{
		return m_IsCameraActive;
	}

	void Camera::update(void)
	{
	}
	void Camera::render(graphics::RenderTarget* renderTarget)
	{
		Application::getInstance()->getActiveScene()->render(this, renderTarget);
	}
} // namespace gg
