#include "core/Scene.h"

#include "component/Camera.h"
#include "entity/GameObject.h"
#include "graphics/Renderer.h"
#include "util/Iterators.h"

namespace gg
{
	Scene::Scene(void)
	{
		m_Renderer = new Renderer();
	}

	Scene::~Scene(void)
	{
		delete m_Renderer;
	}

	void Scene::setActiveCamera(Camera* camera)
	{
		m_ActiveCamera = camera;
	}
	void Scene::setActiveCamera(GameObject* gameObject)
	{
		m_ActiveCamera = gameObject->getComponent<Camera>();
	}
	Camera* Scene::getActiveCamera(void) const
	{
		return m_ActiveCamera;
	}

	void Scene::add(GameObject* gameObject)
	{
		m_GameObjects.push_back(gameObject);
		gameObject->onInit();
	}

	void Scene::onInit(void)
	{
	}
	void Scene::onUnload(void)
	{
	}
	void Scene::onFixedUpdate(void)
	{
		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			_go->onFixedUpdate();
		}
	}
	void Scene::onUpdate(void)
	{
		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			_go->onUpdate();
		}
	}
	void Scene::onRender(void)
	{
		m_ActiveCamera->update();
		m_Renderer->begin();
		// process light
		// process game objects
		// TODO: add children iteration
		const Math::Mat4f& _v = m_ActiveCamera->getViewMatrix();
		const Math::Mat4f& _p = m_ActiveCamera->getProjectionMatrix();
		const Math::Mat4f _pv = _p * _v;

		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _v, _p, _pv, LightSettings);
		}

		// render queues?
	}
} // namespace gg
