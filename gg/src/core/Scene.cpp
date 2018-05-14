#include "core/Scene.h"

#include "component/Camera.h"
#include "component/Light.h"

#include "entity/FreeCamera.h"
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
		if (!camera)
		{
			return;
		}

		if (m_ActiveCamera)
		{
			m_ActiveCamera->setIsCameraActive(false);
		}

		m_ActiveCamera = camera;
		m_ActiveCamera->setIsCameraActive(true);
	}

	void Scene::setActiveCamera(FreeCamera* freeCamera)
	{
		Camera* _camera = freeCamera->getComponent<Camera>();

		if (!_camera)
		{
			return;
		}

		if (m_ActiveCamera)
		{
			m_ActiveCamera->setIsCameraActive(false);
		}

		freeCamera->resetMousePosition();
		m_ActiveCamera = _camera;
		m_ActiveCamera->setIsCameraActive(true);
	}

	void Scene::setActiveCamera(GameObject* gameObject)
	{
		Camera* _camera = gameObject->getComponent<Camera>();
		if (!_camera)
		{
			return;
		}

		setActiveCamera(_camera);
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

		// begin with rendertarget
		m_Renderer->begin();
		renderScene(m_ActiveCamera);

		// draw the quad
		m_Renderer->beginScreen();
		m_Renderer->drawScreen(m_ActiveCamera->getViewProjectionMatrix());

		m_Renderer->clearBuffers();
	}

	void Scene::renderScene(Camera* camera)
	{
		const math::Vec3f& _cameraPosition = camera->getGameObject()->getTransform()->getPosition();
		const math::Vec3f& _cameraForward = camera->getGameObject()->getTransform()->getForward();

		const math::Mat4f& _p = camera->getProjectionMatrix();
		const math::Mat4f& _v = camera->getViewMatrix();
		const math::Mat4f _pv = camera->getViewProjectionMatrix();

		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _p, _v, _pv, _cameraPosition, _cameraForward, LightSettings, m_Lights);
		}

		m_Renderer->drawDebug(_pv);
	}

	void Scene::renderScene(const math::Mat4f& projection, const math::Vec3f& cameraPosition, const math::Quaternion& cameraRotation)
	{
		const math::Vec3f _cameraForward = cameraRotation.getForward();

		const math::Mat4f& _p = m_ActiveCamera->getProjectionMatrix();
		const math::Mat4f& _v = Camera::viewMatrix(cameraPosition, cameraRotation);
		const math::Mat4f _pv = _p * _v;

		VFOR(it, m_GameObjects)
		{
			GameObject* _go = *it;
			m_Renderer->draw(_go, _p, _v, _pv, cameraPosition, _cameraForward, LightSettings, m_Lights);
		}

		m_Renderer->drawDebug(_pv);
	}
} // namespace gg
