#include "TestScene.h"
#include "core/Input.h"
#include "core/Time.h"

namespace GGEngine
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}
	void TestScene::onInit(void)
	{
		//LOG("onInit");
	}
	void TestScene::onUnload(void)
	{
	}
	void TestScene::onFixedUpdate(void)
	{
		//LOG("onFixedUpdate");
	}
	void TestScene::onUpdate(void)
	{
		//LOG("onUpdate");
		if (Input::getKeyDown(KEY::A))
		{
			LOG(Time::getCurrentTime() << ":onUpdate");
		}
	}
} // namespace GGEngine
