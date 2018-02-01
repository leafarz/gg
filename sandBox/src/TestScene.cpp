#include "GL/glew.h"

#include "TestScene.h"

#include "core/Input.h"
#include "core/Time.h"

#include "core/gg.h"

#include "renderer/Shader.h"

#include "platform/opengl/GLCommon.h"

#include "entity/GameObject.h"
#include "component/Transform.h"
#include "math/MathUtil.h"
#include "math/Quaternion.h"

#include "component/Components.h"
#include "component/Component.h"
#include <iostream>
#include <array>
namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	Shader *s;
	GameObject* go;
	void TestScene::onInit(void)
	{
		std::vector<Vertex> _verts = 
		{
			// pos								// uv					// normal						// color
			{ Math::Vec3f( 0.5f,  0.5f, 0.0),	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ Math::Vec3f( 0.5f, -0.5f, 0.0),	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ Math::Vec3f(-0.5f, -0.5f, 0.0),	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ Math::Vec3f(-0.5f,  0.5f, 0.0),	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) }
		};

		std::vector<uint> _indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* _mesh = new Mesh();
		_mesh->setVertices(_verts, _indices);

		go = new GameObject("GameObject");
		MeshRenderer* _mr = go->addComponent<MeshRenderer>();
		_mr->setMesh(_mesh);
		add(go);
		
		s = new Shader("src/basic.shader");
		s->bind();


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
	}

	void TestScene::onRender(void)
	{
		Scene::onRender();
	}
} // namespace gg
