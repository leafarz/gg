#ifndef		GGENGINE_WINDOW_H
#define		GGENGINE_WINDOW_H
#pragma once

#include "GLFW/glfw3.h"
#include <string>

namespace GGEngine
{
	class Window
	{
	public:
		Window(void);
		Window(const std::string& windowName, GLint width, GLint height);
		~Window(void);

		bool			shouldClose(void) const;

		void			setWindowTitle(const std::string& windowName);
		std::string		setWindowTitle(void);
		void			setTitle(const std::string& title);

		void			resizeWindow(GLint width, GLint height) const;

		void			clear(GLuint bits) const;
		void			swapBuffers(void) const;
		void			pollEvents(void) const;

	private:
		GLFWwindow* m_Window;
		std::string m_windowTitle;
	}; // class Window
} // namespace GGEngine

#endif
