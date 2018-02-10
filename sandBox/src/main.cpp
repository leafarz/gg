#include <iostream>

#include "core/Application.h"
#include "TestScene.h"

using namespace gg;

int main()
{
	Application* _app = new Application("Game", 1280, 720);
	_app->addScene(new TestScene(), "TestScene", true);
	_app->run();

	return 0;
}
