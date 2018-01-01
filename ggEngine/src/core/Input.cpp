#include "core/Input.h"
#include "core/gg.h"

namespace gg
{
	GLboolean	Input::s_Keys[(int)KEY::LAST];
	GLboolean	Input::s_KeyDown[(int)KEY::LAST];
	GLboolean	Input::s_KeyUp[(int)KEY::LAST];
	GLushort	Input::s_KeyDownQueue[(int)KEY::LAST];
	GLushort	Input::s_KeyUpQueue[(int)KEY::LAST];

	GLubyte		Input::s_KeyDownCount = 0;
	GLubyte		Input::s_KeyUpCount = 0;

	GLboolean	Input::s_IsKeyboardEnabled = GL_FALSE;

	GLboolean	Input::s_MouseBtns[(int)MOUSE::LAST];
	GLboolean	Input::s_MouseBtnDown[(int)MOUSE::LAST];
	GLboolean	Input::s_MouseBtnUp[(int)MOUSE::LAST];
	GLubyte		Input::s_MouseBtnDownQueue[(int)MOUSE::LAST];
	GLubyte		Input::s_MouseBtnUpQueue[(int)MOUSE::LAST];

	GLubyte		Input::s_MouseBtnDownCount = 0;
	GLubyte		Input::s_MouseBtnUpCount = 0;

	GLboolean	Input::s_IsMouseInputEnabled = GL_FALSE;

	Math::Vec2f Input::s_MousePos;
	
	GLvoid Input::init(GLvoid)
	{
		// initialize arrays
		FOR(0, (int)KEY::LAST)
		{
			s_Keys[i] = GL_FALSE;
			s_KeyDown[i] = GL_FALSE;
			s_KeyUp[i] = GL_FALSE;
			s_KeyDownQueue[i] = GL_FALSE;
			s_KeyUpQueue[i] = GL_FALSE;
		}

		FOR(0, (int)MOUSE::LAST)
		{
			s_MouseBtns[i] = GL_FALSE;
			s_MouseBtnDown[i] = GL_FALSE;
			s_MouseBtnUp[i] = GL_FALSE;
			s_MouseBtnDownQueue[i] = GL_FALSE;
			s_MouseBtnUpQueue[i] = GL_FALSE;
		}
		
		toggleKeyboardInput(GL_TRUE);
		toggleMouseInput(GL_TRUE);
	}

	GLvoid Input::toggleKeyboardInput(GLboolean isActive)
	{
		if (isActive == s_IsKeyboardEnabled) { return; }

		s_IsKeyboardEnabled = isActive;

		GLFWwindow* _window = glfwGetCurrentContext();

		if (isActive)
		{
			glfwSetKeyCallback(_window, keyCallback);
		}
		else
		{
			glfwSetKeyCallback(_window, nullptr);
		}
	}

	GLboolean Input::getKey(KEY key)
	{
		return s_Keys[(int)key];
	}

	GLboolean Input::getKeyDown(KEY key)
	{
		return s_KeyDown[(int)key];
	}

	GLboolean Input::getKeyUp(KEY key)
	{
		return s_KeyUp[(int)key];
	}

	GLvoid Input::clearKeyboardInput(GLvoid)
	{
		FOR(0, s_KeyDownCount)
		{
			s_KeyDown[s_KeyDownQueue[i]] = GL_FALSE;
		}
		FOR(0, s_KeyUpCount)
		{
			s_KeyUp[s_KeyUpQueue[i]] = GL_FALSE;
		}
		s_KeyDownCount = 0;
		s_KeyUpCount = 0;
	}

	GLvoid Input::toggleMouseInput(GLboolean isActive)
	{
		if (isActive == s_IsMouseInputEnabled) { return; }

		s_IsMouseInputEnabled = isActive;

		GLFWwindow* _window = glfwGetCurrentContext();

		if (isActive)
		{
			glfwSetCursorPosCallback(_window, mousePosCallback);
			glfwSetMouseButtonCallback(_window, mouseButtonCallback);
		}
		else
		{
			glfwSetMouseButtonCallback(_window, nullptr);
			glfwSetCursorPosCallback(_window, nullptr);
		}
	}

	GLboolean Input::getMouseButton(MOUSE key)
	{
		return s_MouseBtns[(GLushort)key];
	}

	GLboolean Input::getMouseButtonDown(MOUSE key)
	{
		return s_MouseBtnDown[(GLushort)key];
	}

	GLboolean Input::getMouseButtonUp(MOUSE key)
	{
		return s_MouseBtnUp[(GLushort)key];
	}

	Math::Vec2f Input::getMousePosition(GLvoid)
	{
		return s_MousePos;
	}

	GLvoid Input::clearMouseBtnInput(GLvoid)
	{
		FOR(0, s_MouseBtnDownCount)
		{
			s_MouseBtnDown[s_MouseBtnDownQueue[i]] = GL_FALSE;
		}
		FOR(0, s_MouseBtnUpCount)
		{
			s_MouseBtnUp[s_MouseBtnUpQueue[i]] = GL_FALSE;
		}
		s_MouseBtnDownCount = 0;
		s_MouseBtnUpCount = 0;
	}

	GLvoid Input::setCursorMode(CURSOR_MODE mode)
	{
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, (GLuint)mode);
	}

	GLvoid Input::update(GLvoid)
	{
		clearKeyboardInput();
		clearMouseBtnInput();
	}

	GLvoid Input::keyCallback(GLFWwindow* window, GLint keyIndex, GLint scancode, GLint action, GLint mods)
	{
		s_Keys[keyIndex] = action;

		if (action == GLFW_PRESS)
		{
			s_KeyDown[keyIndex] = GL_TRUE;

			// add key to queue to clear keydown later
			// (instead of flushing all keyDown array)
			s_KeyDownQueue[s_KeyDownCount++] = keyIndex;
		}
		// GLFW_RELEASE
		else
		{
			s_KeyUp[keyIndex] = GL_TRUE;

			// add key to queue to clear keyUp later
			// (instead of flushing all keyUp array)
			s_KeyUpQueue[s_KeyUpCount++] = keyIndex;
		}
	}

	GLvoid Input::mouseButtonCallback(GLFWwindow* window, GLint btnIndex, GLint action, GLint mods)
	{
		s_MouseBtns[btnIndex] = action;

		if (action == GLFW_PRESS)
		{
			s_MouseBtnDown[btnIndex] = GL_TRUE;

			// add mouse button to queue to clear mouseBtnDown later
			// (instead of flushing all mouseBtnDown array)
			s_MouseBtnDownQueue[s_MouseBtnDownCount++] = btnIndex;
		}
		else
		{
			s_MouseBtnUp[btnIndex] = GL_TRUE;

			// add mouse button to queue to clear mouseBtnUp later
			// (instead of flushing all mouseBtnUp array)
			s_MouseBtnUpQueue[s_MouseBtnUpCount++] = btnIndex;
		}
	}

	GLvoid Input::mousePosCallback(GLFWwindow* window, GLdouble x, GLdouble y)
	{
		s_MousePos = Math::Vec2f((float)x, (float)y);
	}
}// namespace gg
