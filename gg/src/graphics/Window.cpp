#include "graphics/Window.h"

namespace gg { namespace graphics {
	Window::Window(void) :
		m_windowTitle(""), m_Width(1280), m_Height(720)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(1280, 720, "", NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);
	}

	Window::Window(const std::string& windowTitle, GLint width, GLint height) :
		m_windowTitle(windowTitle), m_Width(width), m_Height(height)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);
	}

	Window::~Window(void)
	{
		glfwTerminate();
	}

	GLvoid Window::setWindowTitle(const std::string& windowName)
	{
		m_windowTitle = windowName;
	}

	const std::string& Window::getWindowTitle(void)
	{
		return m_windowTitle;
	}

	void Window::setTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}


	bool Window::shouldClose(void) const
	{
		return glfwWindowShouldClose(m_Window);
	}

	GLFWwindow* Window::getWindow(void)
	{
		return m_Window;
	}

	void Window::resizeWindow(int width, int height) const
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	void Window::swapBuffers(void) const
	{
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);
	}

	void Window::pollEvents(void) const
	{
		/* Poll for and process events */
		glfwPollEvents();
	}
	math::Vec2f Window::getSize(void) const
	{
		return math::Vec2f((float)m_Width, (float)m_Height);
	}
	uint Window::getWidth(void) const
	{
		return m_Width;
	}
	uint Window::getHeight(void) const
	{
		return m_Height;
	}
}/*namespace graphics*/ } // namespace gg
