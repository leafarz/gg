#include "component/Camera.h"

#include "entity/GameObject.h"
#include "core/gg.h"
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

	const Math::Mat4f Camera::getViewMatrix(void)
	{
		const Math::Vec3f& _pos = m_GameObject->getTransform()->getPos();
		const Math::Quaternion& _q = m_GameObject->getTransform()->getRotation().conjugate();
		Math::Mat4f _rotMatrix = Math::Mat4f::rotationMatrix(_q);

		float _m00 = _rotMatrix[0]	- _pos.x * _rotMatrix[12];
		float _m10 = _rotMatrix[4]	- _pos.y * _rotMatrix[12];
		float _m20 = _rotMatrix[8]	- _pos.z * _rotMatrix[12];
		float _m30 = _rotMatrix[12];

		float _m01 = _rotMatrix[1]	- _pos.x * _rotMatrix[13];
		float _m11 = _rotMatrix[5]	- _pos.y * _rotMatrix[13];
		float _m21 = _rotMatrix[9]	- _pos.z * _rotMatrix[13];
		float _m31 = _rotMatrix[13];

		float _m02 = _rotMatrix[2]	- _pos.x * _rotMatrix[14];
		float _m12 = _rotMatrix[6]	- _pos.y * _rotMatrix[14];
		float _m22 = _rotMatrix[10] - _pos.z * _rotMatrix[14];
		float _m32 = _rotMatrix[14];

		float _m03 = _rotMatrix[3]	- _pos.x * _rotMatrix[15];
		float _m13 = _rotMatrix[7]	- _pos.y * _rotMatrix[15];
		float _m23 = _rotMatrix[11] - _pos.z * _rotMatrix[15];
		float _m33 = _rotMatrix[15];

		return Math::Mat4f(
			_m00, _m01, _m02, _m03,
			_m10, _m11, _m12, _m13,
			_m20, _m21, _m22, _m23,
			_m30, _m31, _m32, _m33
		);
	}

	const Math::Mat4f Camera::getViewProjectionMatrix(void)
	{
		Transform* _t = m_GameObject->getTransform();
		return m_ProjectionMatrix * getViewMatrix();
	}

	void Camera::update(void)
	{ }
} // namespace gg
