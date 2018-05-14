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


		const math::Mat4f& _p = m_ActiveCamera->getProjectionMatrix();


		// with custom framebuffer
		m_Renderer->begin1();

		const math::Vec3f _newCameraPosition = math::Vec3f(-4,2,0);
		const math::Quaternion _newRotation = math::Quaternion::identity * math::Quaternion(math::Vec3f::up,90);
		renderScene(_p, _newCameraPosition, _newRotation);


		// ---------------------------------------------------------------------------

		// without custom framebuffer
		m_Renderer->begin2();

		const math::Vec3f& _cameraPosition = m_ActiveCamera->getGameObject()->getTransform()->getPosition();
		const math::Vec3f& _cameraDirection = m_ActiveCamera->getGameObject()->getTransform()->getForward();
		const math::Mat4f& _v = m_ActiveCamera->getViewMatrix();
		const math::Mat4f _pv = _p * _v;

		// draw the quad
		m_Renderer->draw2(_pv);
		renderScene(m_ActiveCamera);


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
