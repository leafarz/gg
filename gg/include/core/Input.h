#ifndef		GG_INPUT_H
#define		GG_INPUT_H
#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "core/InputDefines.h"

#include "math/Vec2f.h"

namespace gg
{
	class Input
	{
	private:
		friend class Application;

	public:
#pragma region KEYBOARD
		/* Enable or disable keyboard input. */
		static GLvoid toggleKeyboardInput(GLboolean isEnabled);

		/* Returns flag if specific key is held down. */
		static GLboolean getKey(KEY key);

		/* Returns flag if specific key is pressed. */
		static GLboolean getKeyDown(KEY key);

		/* Returns flag if specific key is released. */
		static GLboolean getKeyUp(KEY key);

		/* Resets all keyboard key variables values to GL_FALSE. */
		static GLvoid clearKeyboardInput(GLvoid);
#pragma endregion KEYBOARD

#pragma region MOUSE
		/* Enable or disable mouse input. */
		static GLvoid toggleMouseInput(GLboolean isEnabled);

		/* Returns flag if specific mouse button is held down. */
		static GLboolean getMouseButton(MOUSE key);

		/* Returns flag if specific mouse button is pressed. */
		static GLboolean getMouseButtonDown(MOUSE key);

		/* Returns flag if specific mouse button is released. */
		static GLboolean getMouseButtonUp(MOUSE key);

		/* Returns the current position of the mouse cursor. */
		static Math::Vec2f getMousePosition(GLvoid);

		/* Returns the delta of the mouse wheel. */
		static Math::Vec2f getMouseWheelDelta(GLvoid);

		/* Resets all mouse button variables values to GL_FALSE. */
		static GLvoid clearMouseBtnInput(GLvoid);
#pragma endregion MOUSE

		static GLvoid setCursorMode(CURSOR_MODE mode);

	private:
		/* Initializes array values and initializes keyboard and mouse callbacks. */
		static GLvoid init(GLvoid);

		/* Callback for setting keyboard variables. */
		static GLvoid keyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);

		/* Callback for setting mouse variables. */
		static GLvoid mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);

		/* Callback for setting mouse pos variable. */
		static GLvoid mousePosCallback(GLFWwindow* window, GLdouble x, GLdouble y);

		/* Callback for mouse scroll wheel. */
		static GLvoid mouseScrollCallback(GLFWwindow* window, GLdouble xOffset, GLdouble yOffset);

		/* Clears keyboard and mouse data. Must be called before poll events */
		static GLvoid update(GLvoid);

	private:
		/* Flag array if keyboard button is held down. */
		static GLboolean s_Keys[(int)KEY::LAST];

		/* Flag array if keyboard button is pressed. */
		static GLboolean s_KeyDown[(int)KEY::LAST];

		/* Flag array if keyboard button is released. */
		static GLboolean s_KeyUp[(int)KEY::LAST];

		/* Lookup table for clearing keyDown array on update.
		 * Key index is added when pressed down.
		*/
		static GLushort s_KeyDownQueue[(int)KEY::LAST];

		/* Lookup table for clearing keyUp array on update.
		* Key index is added when released.
		*/
		static GLushort s_KeyUpQueue[(int)KEY::LAST];

		/* Counter for how many keys are pressed
		 * before going to Update function.
		*/
		static GLubyte s_KeyDownCount;

		/* Counter for how many keys are released
		* before going to Update function.
		*/
		static GLubyte s_KeyUpCount;

		/* Flag for keyboard input if enabled */
		static GLboolean s_IsKeyboardEnabled;

		/* Flag array if mouse button is held down. */
		static GLboolean s_MouseBtns[(int)MOUSE::LAST];

		/* Flag array if mouse button is pressed. */
		static GLboolean s_MouseBtnDown[(int)MOUSE::LAST];

		/* Flag array if mouse button is released. */
		static GLboolean s_MouseBtnUp[(int)MOUSE::LAST];

		/* Lookup table for clearing mouseBtnDown array on update.
		* Mouse button index is added when pressed down.
		*/
		static GLubyte s_MouseBtnDownQueue[(int)MOUSE::LAST];

		/* Lookup table for clearing mouseBtnUp array on update.
		* Mouse button index is added when released.
		*/
		static GLubyte s_MouseBtnUpQueue[(int)MOUSE::LAST];

		/* Position of mouse in vec2f form.*/
		static Math::Vec2f s_MousePos;

		/* Value of mouse scroll wheel delta value */
		static Math::Vec2f s_MouseWheelDelta;

		/* Counter for how many mouse buttons are pressed
		* before going to Update function.
		*/
		static GLubyte s_MouseBtnDownCount;

		/* Counter for how many mouse buttons are released
		* before going to Update function.
		*/
		static GLubyte s_MouseBtnUpCount;

		/* Flag for mouse input if enabled */
		static GLboolean s_IsMouseInputEnabled;
	};// class Input
}// namespace gg
#endif