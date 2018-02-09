#include "core/Scene.h"

#include "core/gg.h"
#include "component/Camera.h"
#include "entity/GameObject.h"
#include "renderer/Renderer.h"

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

	void Scene::add(GameObject * gameObject)
	{
		m_GameObjects.push_back(gameObject);
	}

	void Scene::onInit(void)
	{
	}
	void Scene::onUnload(void)
	{
	}
	void Scene::onFixedUpdate(void)
	{
	}
	void Scene::onUpdate(void)
	{
	}
	void Scene::onRender(void)
	{
		m_ActiveCamera->update();
		m_Renderer->begin();
		// process light
		Math::Mat4f _pvMatrix = m_ActiveCamera->getViewProjectionMatrix();
		// process game objects
		// TODO: add children iteration
		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _pvMatrix);
		}

		// render queues?
	}
} // namespace gg
