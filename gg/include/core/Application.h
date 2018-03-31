#ifndef		GG_APPLICATION_H
#define		GG_APPLICATION_H
#pragma once

#include "GL/glew.h"

#include <vector>
#include <unordered_map>

#include "graphics/Window.h"
#include "graphics/Renderer.h"

namespace gg
{
	class Scene;
	class Application
	{
	public:
		Application(const char* windowName, GLint width, GLint height);
		~Application(void);

		static Application* getInstance(void) { return s_Instance; }

		void run(void);

		Scene* getActiveScene(void) { return m_ActiveScene; }
		void addScene(Scene* scene, const std::string& sceneName, GLboolean setAsActive = false);
		void unloadScene(void);
		GLboolean setScene(const std::string& sceneName);

		void setTimeStep(GLuint fps);
		void setFixedTimeStep(GLuint fps);

	private:
		Application(void) = delete;

		void stop(void);

	private:
		static Application* s_Instance;

		graphics::Window* m_Window;
		GLdouble m_TimeStep;
		GLdouble m_FixedTimeStep;
		GLboolean m_IsRunning;

		Scene* m_ActiveScene;
		bool m_SceneIsInitialized = false;

		std::unordered_map<std::string, Scene*> m_Scenes;
	}; // class Application
} // namespace gg

#endif
