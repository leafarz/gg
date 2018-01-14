#ifndef		GG_SCENE_H
#define		GG_SCENE_H
#pragma once

namespace gg
{
	class Camera;
	class Renderer;
	class Scene
	{
	public:
		Scene(void);
		~Scene(void);

		void	setActiveCamera(Camera* camera);
		Camera* getActiveCamera(void) const;

		virtual void onInit(void);
		virtual void onUnload(void);
		virtual void onFixedUpdate(void);
		virtual void onUpdate(void);
		virtual void onRender(void);

	private:
		Camera* m_ActiveCamera;
		Renderer* m_Renderer;
	}; // class Scene
} // namespace gg

#endif
