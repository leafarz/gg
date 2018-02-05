#include "GL/glew.h"

#include "TestScene.h"

#include "core/Input.h"
#include "core/Time.h"

#include "core/gg.h"

#include "renderer/Shader.h"
#include "renderer/Material.h"

#include "platform/opengl/GLCommon.h"

#include "entity/GameObject.h"
#include "component/Transform.h"
#include "math/MathUtil.h"
#include "math/Quaternion.h"

#include "component/Components.h"
#include "component/Component.h"
#include <iostream>
#include <array>
#include <stack>
namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	Shader *s;
	GameObject *go, *go2;
	void TestScene::onInit(void)
	{
		std::vector<Vertex> _verts = 
		{
			// pos								// uv					// normal						// color
			{ Math::Vec3f( 0.5f-1,  0.5f, 0.0),	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ Math::Vec3f( 0.5f-1, -0.5f, 0.0),	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ Math::Vec3f(-0.5f-1, -0.5f, 0.0),	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ Math::Vec3f(-0.5f-1,  0.5f, 0.0),	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) }
		};

		std::vector<Vertex> _verts2 = 
		{
			// pos								// uv					// normal						// color
			{ Math::Vec3f( 0.5f+1,  0.5f, 0.0),	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ Math::Vec3f( 0.5f+1, -0.5f, 0.0),	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ Math::Vec3f(-0.5f+1, -0.5f, 0.0),	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ Math::Vec3f(-0.5f+1,  0.5f, 0.0),	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) }
		};

		std::vector<uint> _indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Math::Mat4f m = Math::Mat4f(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
		Math::Mat4f v = Math::Mat4f(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 1,
			0, 0, 0, 1
		);
		Math::Mat4f p = Math::Mat4f::perspectiveMatrix(103, 16.0f / 9.0f, 0.1f, 1000);

		Mesh* _mesh = new Mesh();
		_mesh->setVertices(_verts, _indices);
		go = new GameObject("GameObject");
		MeshRenderer* _mr = go->addComponent<MeshRenderer>();
		_mr->setMesh(_mesh);
		Material* _mat1 = new Material(new Shader("src/basic.shader"));

		_mr->setMaterial(_mat1);

		GameObject* _camera = new GameObject("Camera");
		Camera* _cam = _camera->addComponent<Camera>();
		_cam->setPerspectiveCamera(103, 16.0f / 9.0f, 0.1f, 1000);
		//add(_camera);
		setActiveCamera(_cam);
		Math::Mat4f _pvMatrix = _cam->getViewProjectionMatrix();
		
		_mat1->setUniform("mvp", p * v * m);
		// TODO: check view matrix if correct
		LOG("V======================");
		LOG(v);
		LOG(_cam->getViewMatrix());
		add(go);

		Mesh* _mesh2 = new Mesh();
		_mesh2->setVertices(_verts2, _indices);
		go2 = new GameObject("GameObject");
		MeshRenderer* _mr2 = go2->addComponent<MeshRenderer>();
		_mr2->setMesh(_mesh2);
		Material* _mat2 = new Material(new Shader("src/basic.shader"));
		go->addChild(go2);

		//s = new Shader("src/basic.shader");
		//s->bind();

		//Math::Mat4f tm = Math::Mat4f::translationMatrix(Math::Vec3f(0, 0, 0));
		//Math::Mat4f rm = Math::Mat4f::rotationMatrixd(Math::Vec3f::zero);
		//Math::Mat4f sm = Math::Mat4f::scaleMatrix(1);

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
		if (Input::getKey(KEY::A))
		{
			//v[11] += 0.1f;
		}
		//v[11] = 1;
		
		//s->setUniform("mvp", p*v*m, false);
		//go->getComponent<MeshRenderer>()->getMaterial()->getShader()->setUniform("mvp", p*v*m, false);
		Scene::onRender();
	}
} // namespace gg
