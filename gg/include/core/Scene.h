#ifndef		GG_SCENE_H
#define		GG_SCENE_H
#pragma once

#include <vector>

#include "graphics/LightSettings.h"

#include "math/Vec3f.h"

namespace gg { class Camera; class GameObject; class Light; }
namespace gg { namespace graphics { class Renderer; } }

namespace gg
{
	class Scene
	{
	public:
		Scene(void);
		~Scene(void);

		void	setActiveCamera(Camera* camera);
		void	setActiveCamera(GameObject* gameObject);
		Camera* getActiveCamera(void) const;

		graphics::Renderer* getRenderer(void) { return m_Renderer; }

		void	add(GameObject* gameObject);
		// TODO: add remove function

		virtual void onInit(void);
		virtual void onUnload(void);
		virtual void onFixedUpdate(void);
		virtual void onUpdate(void);
		virtual void onRender(void);

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
