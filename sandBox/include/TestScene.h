#ifndef		GGENGINE_TESTSCENE_H
#define		GGENGINE_TESTSCENE_H
#pragma once

#include "core/Scene.h"
#include "core/gg.h"

namespace GGEngine
{
	class TestScene : public Scene
	{
	public:
		TestScene(void);
		~TestScene(void);

		void onInit(void) override;
		void onUnload(void) override;
		void onFixedUpdate(void) override;
		void onUpdate(void) override;
	}; // class TestScene
} // namespace GGEngine

#endif
