#include "core/Application.h"
#include "core/gg.h"
#include "core/Scene.h"
#include "core/Input.h"
#include "core/Time.h"

#include "util/Resource.h"
namespace gg
{
	Application::Application(const char* windowName, GLint width = 1280, GLint height = 720) :
		m_TimeStep(1 / 60.0),
		m_FixedTimeStep(1 / 60.0),
		m_IsRunning(false),
		m_ActiveScene(nullptr)
	{
		m_Window = new Window(windowName, width, height);

		// glew init
		glewExperimental = GL_TRUE;
		if (GLenum err = glewInit() != GLEW_OK) { LOG("[Error] " << glewGetErrorString(err)); }

		Input::init();
		Time::s_FixedDelta = m_FixedTimeStep;

	}

	Application::~Application(void)
	{
		delete m_Window;
	}

	void Application::run(void)
	{
		if (m_IsRunning) { return; }

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

			GLdouble _currTime = Time::getCurrentTime();
			GLdouble _delta = _currTime - _prevTime;
			_prevTime = _currTime;

			_timer += _delta;
			_fixedTimer += _delta;

			GLboolean _willUpdate = _timer >= m_TimeStep;

			if (_willUpdate)
			{
				// update input
				Input::update();
				m_Window->pollEvents();

				// update delta time
				GLdouble _rem = std::fmod(_timer, m_TimeStep);
				Time::s_Delta = _timer - _rem;
				_timer = _rem;
			}

			// physics update
			GLuint _fixedSteps = (GLuint)(_fixedTimer / m_FixedTimeStep);
			if (_fixedSteps > 0)
			{
				FORU(i, 0, _fixedSteps)
				{
					if (m_ActiveScene != nullptr) { m_ActiveScene->onFixedUpdate(); }
				}
				_fixedTimer -= _fixedSteps * m_FixedTimeStep;
			}

			if (_willUpdate)
			{
				if (m_ActiveScene != nullptr)
				{
					// update
					m_ActiveScene->onUpdate();

					// render
					m_ActiveScene->onRender();

					// swap
					m_Window->swapBuffers();
				}
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
		}
	}

	void Application::stop(void)
	{
		if (!m_IsRunning) { return; }
		m_IsRunning = false;
	}

	void Application::addScene(Scene * scene, const std::string& sceneName, GLboolean setAsActive)
	{
		m_Scenes.insert({ sceneName, scene });

		unloadScene();
		m_ActiveScene = scene;
		m_ActiveScene->onInit();
	}

	void Application::unloadScene(void)
	{
		if (m_ActiveScene == nullptr) { return; }

		m_ActiveScene->onUnload();
		m_ActiveScene = nullptr;
	}

	GLboolean Application::setScene(const std::string& sceneName)
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

	void Application::setTimeStep(GLuint fps)
	{
		m_TimeStep = 1 / (GLdouble)fps;
	}

	void Application::setFixedTimeStep(GLuint fps)
	{
		m_FixedTimeStep = 1 / (GLdouble)fps;
		Time::s_FixedDelta = m_FixedTimeStep;
	}
} // namespace gg
