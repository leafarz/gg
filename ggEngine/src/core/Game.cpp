#include "core/Game.h"
#include "core/gg.h"
#include "core/Scene.h"
#include "core/Input.h"
#include "core/Time.h"
namespace GGEngine
{
	Game::Game(const char* windowName, GLint width = 1280, GLint height = 720) :
		m_TimeStep(1 / 60.0),
		m_FixedTimeStep(1 / 60.0),
		m_IsRunning(false),
		m_ActiveScene(nullptr)
	{
		m_Window = new Window(windowName, width, height);

		Input::init();
		Time::s_FixedDelta = m_FixedTimeStep;
	}

	Game::~Game(void)
	{
		delete m_Window;
	}

	void Game::run(void)
	{
		m_IsRunning = GL_TRUE;
		GLdouble _prevTime = Time::getCurrentTime();

		GLdouble _timer = 0;
		GLdouble _fixedTimer = 0;

		GLdouble _fpsTimer = 0;
		GLuint _frameCount = 0;

		Time::s_StartTime = _prevTime;
		while (m_IsRunning)
		{
			if (m_Window->shouldClose()) { stop(); }

			m_Window->clear(GL_COLOR_BUFFER_BIT);
			m_Window->swapBuffers();

			GLdouble _currTime = Time::getCurrentTime();
			GLdouble _delta = _currTime - _prevTime;
			_prevTime = _currTime;

			_timer += _delta;
			_fixedTimer += _delta;

			// input update
			if (_timer >= m_TimeStep)
			{
				Input::update();
				m_Window->pollEvents();
			}

			// physics update
			GLuint _fixedSteps = (GLuint)(_fixedTimer / m_FixedTimeStep);
			if (_fixedSteps > 0)
			{
				FOR(0, _fixedSteps)
				{
					if (m_ActiveScene != nullptr) { m_ActiveScene->onFixedUpdate(); }
				}
				_fixedTimer -= _fixedSteps * m_FixedTimeStep;
			}

			// update
			if (_timer >= m_TimeStep)
			{
				GLdouble _rem = std::fmod(_timer, m_TimeStep);
				Time::s_Delta = _timer - _rem;
				if (m_ActiveScene != nullptr) { m_ActiveScene->onUpdate(); }
				_timer = _rem;

				++_frameCount;
			}

			// TODO: eventually remove this
			// display fps for window
			if ((_fpsTimer += _delta) >= 1)
			{
				m_Window->setTitle(m_Window->setWindowTitle() + " (FPS:" + std::to_string(_frameCount) + ")");

				_frameCount = 0;
				_fpsTimer = 0;
			}

			// render
			if (m_ActiveScene != nullptr) { m_ActiveScene->onRender(); }
		}
	}

	void Game::stop(void)
	{
		if (!m_IsRunning) { return; }
		m_IsRunning = false;
	}

	void Game::addScene(Scene * scene, const std::string& sceneName, GLboolean setAsActive)
	{
		m_Scenes.insert({ sceneName, scene });

		unloadScene();
		m_ActiveScene = scene;
		m_ActiveScene->onInit();
	}

	void Game::unloadScene(void)
	{
		if (m_ActiveScene == nullptr) { return; }

		m_ActiveScene->onUnload();
		m_ActiveScene = nullptr;
	}

	GLboolean Game::setScene(const std::string& sceneName)
	{
		if (m_Scenes.find(sceneName) == m_Scenes.end())
		{
			return false;
		}
		unloadScene();
		m_ActiveScene = m_Scenes[sceneName];
		m_ActiveScene->onInit();
		return true;
	}

	void Game::setTimeStep(GLuint fps)
	{
		m_TimeStep = 1 / (GLdouble)fps;
	}

	void Game::setFixedTimeStep(GLuint fps)
	{
		m_FixedTimeStep = 1 / (GLdouble)fps;
		Time::s_FixedDelta = m_FixedTimeStep;
	}
} // namespace GGEngine
