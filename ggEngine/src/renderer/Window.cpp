#include "renderer/Window.h"

namespace GGEngine
{
	Window::Window(void)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(1280, 720, "", NULL, NULL);
		m_windowTitle = "";

		if (!m_Window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);
	}

	Window::Window(const std::string& windowName, GLint width, GLint height)
	{
		/* Initialize the library */
		if (!glfwInit()) { return; }

		/* Create a windowed mode window and its OpenGL context */
		m_Window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
		m_windowTitle = windowName;

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

	std::string Window::setWindowTitle(void)
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

	void Window::resizeWindow(GLint width, GLint height) const
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	void Window::clear(GLuint bits) const
	{
		glClear(bits);
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
} // namespace GGEngine
