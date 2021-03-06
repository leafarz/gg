#include "entity/FreeCamera.h"

#include "core/Input.h"
#include "component/Camera.h"

#include "math/MathUtil.h"
#include "math/Quaternion.h"
#include "math/Vec3f.h"

namespace gg
{
	FreeCamera::FreeCamera(void)
		: GameObject("FreeCamera")
	{
		m_Camera = addComponent<Camera>();
	}

	FreeCamera::FreeCamera(float fovDeg, float aspectRatio, float zNear, float zFar)
		: GameObject("FreeCamera")
	{
		m_Camera = addComponent<Camera>();
		m_Camera->setPerspective(fovDeg, aspectRatio, zNear, zFar);
	}

	FreeCamera::~FreeCamera(void)
	{
		// TODO: remove component or delete?
	}


	void FreeCamera::setMoveSpeed(float moveSpeed)
	{
		m_MoveSpeed = moveSpeed;
	}

	void FreeCamera::resetMousePosition(void)
	{
		m_PrevMousePos = Input::getMousePosition();
		Input::setCursorMode(CURSOR_MODE::DISABLED);
	}

	void FreeCamera::onInit(void)
	{
		resetMousePosition();
	}

	void FreeCamera::onUpdate(void)
	{
		if (!m_Camera->isCameraActive())
		{
			return;
		}

		const math::Vec3f& _pos = m_Transform->getPosition();
		const math::Quaternion& _rot = m_Transform->getRotation();
		const math::Vec3f& _euler = m_Transform->getEuler();

		if (Input::getKey(KEY::W))
		{
			m_Transform->setPosition(_pos + _rot.getForward() * m_MoveSpeed);
		}
		if (Input::getKey(KEY::S))
		{
			m_Transform->setPosition(_pos - _rot.getForward() * m_MoveSpeed);
		}
		if (Input::getKey(KEY::D))
		{
			m_Transform->setPosition(_pos + _rot.getRight() * m_MoveSpeed);
		}
		if (Input::getKey(KEY::A))
		{
			m_Transform->setPosition(_pos - _rot.getRight() * m_MoveSpeed);
		}
		if (Input::getKey(KEY::E))
		{
			m_Transform->setPosition(_pos + _rot.getUp() * m_MoveSpeed);
		}
		if (Input::getKey(KEY::Q))
		{
			m_Transform->setPosition(_pos - _rot.getUp() * m_MoveSpeed);
		}

		if (Input::getKeyDown(KEY::ESCAPE))
		{
			m_IsCursorVisible = !m_IsCursorVisible;
			if (m_IsCursorVisible)
			{
				Input::setCursorMode(CURSOR_MODE::VISIBLE);
			}
			else
			{
				resetMousePosition();
			}
		}

		if (Input::getMouseButtonDown(MOUSE::RIGHT))
		{
			m_IsCursorVisible = false;
			resetMousePosition();
		}
		else if (Input::getMouseButtonUp(MOUSE::RIGHT))
		{
			m_IsCursorVisible = true;
			Input::setCursorMode(CURSOR_MODE::VISIBLE);
		}

		if (m_IsCursorVisible) { return; }

		math::Vec2f _delta = Input::getMousePosition() - m_PrevMousePos;

		m_Transform->setEulerX(_euler.x + _delta.y * m_Sensitivity);
		m_Transform->setEulerY(_euler.y + _delta.x * m_Sensitivity);

		m_PrevMousePos = Input::getMousePosition();

		float _wheel = Input::getMouseWheelDelta().y;
		if (_wheel != 0)
		{
			m_Sensitivity = math::clamp(m_Sensitivity + _wheel * 0.01f, m_SensitivityBounds.x, m_SensitivityBounds.y);
		}
	}
} // namespace gg
