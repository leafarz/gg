#include "core/Scene.h"

#include "component/Camera.h"
#include "component/Light.h"
#include "entity/GameObject.h"
#include "graphics/Renderer.h"
#include "util/Iterators.h"

namespace gg
{
	Scene::Scene(void)
	{
		m_Renderer = new graphics::Renderer();
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

		std::vector<Light*> _light = gameObject->getComponents<Light>();
		VFOR(it, _light) { m_Lights.push_back(*it); }

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

		// process light
		// process game objects
		// TODO: add children iteration
		const math::Mat4f& _v = m_ActiveCamera->getViewMatrix();
		const math::Mat4f& _p = m_ActiveCamera->getProjectionMatrix();
		const math::Mat4f _pv = _p * _v;

		const math::Vec3f& _cameraPosition = m_ActiveCamera->getGameObject()->getTransform()->getPosition();
		const math::Vec3f& _cameraDirection = m_ActiveCamera->getGameObject()->getTransform()->getForward();


		// with custom framebuffer
		m_Renderer->begin1();


		// + draw scene
		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _v, _p, _pv, _cameraPosition, _cameraDirection, LightSettings, m_Lights);
		}
		m_Renderer->drawDebug(_pv);
		// - draw scene

		// without custom framebuffer
		m_Renderer->begin2();

		// draw the quad
		m_Renderer->draw2(_pv);

		// + draw scene
		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _v, _p, _pv, _cameraPosition, _cameraDirection, LightSettings, m_Lights);
		}
		m_Renderer->drawDebug(_pv);
		// - draw scene


		m_Renderer->clearBuffers();
	}
} // namespace gg
