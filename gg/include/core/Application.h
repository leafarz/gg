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

		Scene* getActiveScene(void);
		/* Adds the scene to list. Calls onInit() if set as active scene before onRender. */
		void addScene(Scene* scene, const std::string& sceneName, bool setAsActive = false);
		void unloadScene(void);
		/* Sets the scene via the scene name set. Calls onInit() of the scene before onRender. */
		bool setScene(const std::string& sceneName);

		void setTimeStep(uint fps);
		uint getTimeStep(void) const;

		void setFixedTimeStep(uint fps);
		uint getFixedTimeStep(void) const;

		graphics::Window* getWindow(void) const;

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
