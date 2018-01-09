#ifndef		GG_SCENE_H
#define		GG_SCENE_H
#pragma once

namespace gg
{
	class Camera;
	class Scene
	{
	public:
		Scene(void);
		~Scene(void);

		virtual void onInit(void);
		virtual void onUnload(void);
		virtual void onFixedUpdate(void);
		virtual void onUpdate(void);
		virtual void onRender(void);

		void	setActiveCamera(Camera* camera);
		Camera* getActiveCamera(void) const;

	private:
		Camera* m_ActiveCamera;
	}; // class Scene
} // namespace gg

#endif
