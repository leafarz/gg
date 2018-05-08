#ifndef		GG_WINDOW_H
#define		GG_WINDOW_H
#pragma once

#include <string>

#include "GLFW/glfw3.h"
#include "core/Types.h"

#include "math/Vec2f.h"

namespace gg {
// forward declarations
class Application;
namespace graphics {
	class Window
	{
	private:
		friend class Application;

	public:
		/* Sets the windowTitle member string variable. */
		void setWindowTitle(const std::string& windowName);
		/* Gets the windowTitle member string variable. */
		const std::string& getWindowTitle(void);

		void resizeWindow(int width, int height) const;

		math::Vec2f getSize(void) const;
		uint getWidth(void) const;
		uint getHeight(void) const;

	private:
		Window(void);
		Window(const std::string& windowTitle, GLint width, GLint height);
		~Window(void);

		GLFWwindow* getWindow(void);

		/* Sets the title of the glfw window.
		 * This is different from setWindowTitle function.
		 */
		void setTitle(const std::string& title);
		bool shouldClose(void) const;
		void swapBuffers(void) const;
		void pollEvents(void) const;

	private:
		GLFWwindow* m_Window;
		std::string m_windowTitle;

		uint m_Width;
		uint m_Height;
	}; // class Window
}/*namespace graphics*/ } // namespace gg

#endif
