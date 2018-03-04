#include "component/Camera.h"

#include "entity/GameObject.h"

namespace gg
{
	Camera::Camera(void)
	{ }
	Camera::Camera(float fovDeg, float aspectRatio, float zNear, float zFar)
		: m_ProjectionMatrix(Math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar))
	{ }

	Camera::~Camera(void)
	{ }

	void Camera::setPerspectiveCamera(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		m_ProjectionMatrix = Math::Mat4f::perspectiveMatrix(fovDeg, aspectRatio, zNear, zFar);
	}

	const Math::Mat4f& Camera::getProjectionMatrix(void) const
	{
		return m_ProjectionMatrix;
	}

	const Math::Mat4f& Camera::getViewMatrix(void)
	{
		const Transform* const _t = m_GameObject->getTransform();

		if (_t->isDirty())
		{
			const Math::Vec3f& _pos = _t->getPosition();
			const Math::Quaternion& _q = _t->getRotation().conjugate();
			Math::Mat4f _rotMatrix = Math::Mat4f::rotationMatrix(_q);

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

	const Math::Mat4f Camera::getViewProjectionMatrix(void)
	{
		return getProjectionMatrix() * getViewMatrix();
	}

	void Camera::update(void)
	{ }
} // namespace gg
