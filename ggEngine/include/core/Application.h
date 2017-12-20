#ifndef		GGENGINE_APPLICATION_H
#define		GGENGINE_APPLICATION_H
#pragma once

#include "renderer/Window.h"
#include "core/gg.h"
#include <vector>
#include <unordered_map>

namespace GGEngine
{
	class Scene;
	class Application
	{
	public:
		Application(void) = delete;
		Application(const char* windowName, GLint width, GLint height);
		~Application(void);

		void run(void);
		void stop(void);

		void		addScene(Scene* scene, const std::string& sceneName, GLboolean setAsActive = false);
		void		unloadScene(void);
		GLboolean	setScene(const std::string& sceneName);

		void		setTimeStep(GLuint fps);
		void		setFixedTimeStep(GLuint fps);

	private:
		Window*			m_Window;
		GLdouble		m_TimeStep;
		GLdouble		m_FixedTimeStep;
		GLboolean		m_IsRunning;

		Scene*			m_ActiveScene;

		std::unordered_map<std::string, Scene*> m_Scenes;

	}; // class Application
} // namespace GGEngine

#endif
