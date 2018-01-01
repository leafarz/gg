#include "core/Scene.h"

namespace gg
{
	Scene::Scene(void)
	{
	}

	Scene::~Scene(void)
	{
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
	}
	void Scene::setActiveCamera(Camera* camera)
	{
		m_ActiveCamera = camera;
	}
	Camera* Scene::getActiveCamera(void) const
	{
		return m_ActiveCamera;
	}
} // namespace gg
