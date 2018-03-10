#ifndef		GG_WINDOW_H
#define		GG_WINDOW_H
#pragma once

#include <string>

#include "GLFW/glfw3.h"

namespace gg { namespace graphics {
	class Window
	{
	public:
		Window(void);
		Window(const std::string& windowTitle, GLint width, GLint height);
		~Window(void);

		bool			shouldClose(void) const;

		void			setWindowTitle(const std::string& windowName);
		std::string		setWindowTitle(void);
		void			setTitle(const std::string& title);

		void			resizeWindow(GLint width, GLint height) const;

		void			swapBuffers(void) const;
		void			pollEvents(void) const;

	private:
		GLFWwindow* m_Window;
		std::string m_windowTitle;
	}; // class Window
}/*namespace graphics*/ } // namespace gg

#endif
