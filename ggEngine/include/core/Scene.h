#ifndef		GGENGINE_SCENE_H
#define		GGENGINE_SCENE_H
#pragma once

namespace GGEngine
{
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
	}; // class Scene
} // namespace GGEngine

#endif
