#ifndef		GG_TESTSCENE_H
#define		GG_TESTSCENE_H
#pragma once

#include "core/Scene.h"

namespace gg
{
	class TestScene : public Scene
	{
	public:
		using Scene::onRender;

		TestScene(void);
		~TestScene(void);

		void onInit(void) override;
		void onUpdate(void) override;
	}; // class TestScene
} // namespace gg

#endif
