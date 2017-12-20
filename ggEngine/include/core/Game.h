#ifndef		GGENGINE_GAME_H
#define		GGENGINE_GAME_H
#pragma once

#include "renderer/Window.h"
#include "core/gg.h"
#include <vector>
#include <unordered_map>

namespace GGEngine
{
	class Scene;
	class Game
	{
	public:
		Game(void) = delete;
		Game(const char* windowName, GLint width, GLint height);
		~Game(void);

		void init(void);
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

	}; // class Game
} // namespace GGEngine

#endif
