#ifndef		GG_SCENE_H
#define		GG_SCENE_H
#pragma once

#include <vector>

#include "graphics/LightSettings.h"

#include "math/Vec3f.h"
#include "math/Mat4f.h"
#include "math/Quaternion.h"

namespace gg { class Camera; class FreeCamera; class GameObject; class Light; }
namespace gg { namespace graphics { class Material; class Renderer; class RenderTarget; } }

namespace gg
{
	class Scene
	{
	private:
		friend class Application;

	public:
		Scene(void);
		~Scene(void);

		inline Camera* getActiveCamera(void) const { return m_ActiveCamera; }

		void setActiveCamera(Camera* camera);
		void setActiveCamera(GameObject* gameObject);
		void setActiveCamera(FreeCamera* freeCamera);

		graphics::Renderer* getRenderer(void) { return m_Renderer; }

		void	add(GameObject* gameObject);
		// TODO: add remove function

		void render(Camera* camera, graphics::RenderTarget* renderTarget, graphics::Material* material);

	protected:
		virtual void onInit(void);
		virtual void onUnload(void);
		virtual void onFixedUpdate(void);
		virtual void onUpdate(void);
		virtual void onRender(void);

		virtual void renderScene(Camera* camera);
		virtual void renderScene(const math::Mat4f& projection, const math::Vec3f& cameraPosition, const math::Quaternion& cameraRotation);

	public:
		graphics::LightSettings LightSettings;

	private:
		Camera* m_ActiveCamera;
		graphics::Renderer* m_Renderer;

		std::vector<GameObject*> m_GameObjects;
		std::vector<Light*> m_Lights;
	}; // class Scene
} // namespace gg

#endif
