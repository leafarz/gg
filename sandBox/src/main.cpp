#include <iostream>

#include "core/Application.h"
//#include "util/Resource.h"
//#include "math/Vec2f.h"
//#include "math/Vec3f.h"
//#include "math/Mat4f.h"
//#include "../../deps/glm-0.9.7.6/glm/glm.hpp"
#include "TestScene.h"

using namespace gg;
//using namespace GGEngine::Math;

int main()
{
	Application* _app = new Application("Game", 1280, 720);
	_app->addScene(new TestScene(), "TestScene", true);
	_app->run();
	
	//Vec2f v21 = Vec2f(0, 1);
	//Vec2f v22 = Vec2f(1, 0);
	//std::cout << v21.dot(v22) << std::endl;

	//Vec3f v31 = Vec3f(1, 0, 0);
	//Vec3f v32 = Vec3f(0, 1, 0);
	//std::cout << v31.dot(v32) << std::endl;
	//std::cout << v31.cross(v32) << std::endl;

	//Mat4f m = Mat4f();
	//m.setDiagonal(5/99999);
	//std::cout << m << std::endl;
	//
	//glm::vec3 t1 = glm::vec3(1, 0, 0);
	//glm::vec3 t2 = glm::vec3(0, 1, 0);
	//std::cout << glm::cross(t1, t2).x << "," << glm::cross(t1, t2).y << "," << glm::cross(t1, t2).z << "\n";

	return -1;
}
