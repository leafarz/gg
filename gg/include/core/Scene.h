#ifndef		GG_SCENE_H
#define		GG_SCENE_H
#pragma once

#include <vector>

namespace gg
{
	class Camera;
	class Renderer;
	class GameObject;
	class Scene
	{
	public:
		Scene(void);
		~Scene(void);

		void	setActiveCamera(Camera* camera);
		Camera* getActiveCamera(void) const;

		void	add(GameObject* gameObject);
		// TODO: add remove function

		virtual void onInit(void);
		virtual void onUnload(void);
		virtual void onFixedUpdate(void);
		virtual void onUpdate(void);
		virtual void onRender(void);

	private:
		Camera* m_ActiveCamera;
		Renderer* m_Renderer;

		std::vector<GameObject*> m_GameObjects;
	}; // class Scene
} // namespace gg

#endif
