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
	GameObject* _camera;
	void TestScene::onInit(void)
	{
		Math::Vec3f _ulf = Math::Vec3f(-0.5f,  0.5f, -0.5);
		Math::Vec3f _urf = Math::Vec3f( 0.5f,  0.5f, -0.5);
		Math::Vec3f _llf = Math::Vec3f(-0.5f, -0.5f, -0.5);
		Math::Vec3f _lrf = Math::Vec3f( 0.5f, -0.5f, -0.5);

		Math::Vec3f _ulb = Math::Vec3f(-0.5f,  0.5f, 0.5);
		Math::Vec3f _urb = Math::Vec3f( 0.5f,  0.5f, 0.5);
		Math::Vec3f _llb = Math::Vec3f(-0.5f, -0.5f, 0.5);
		Math::Vec3f _lrb = Math::Vec3f( 0.5f, -0.5f, 0.5);

		std::vector<Vertex> _verts =
		{
			// pos	// uv					// normal						// color
			{ _urf,	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ _lrf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ _llf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ _ulf,	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) },

			// pos	// uv					// normal						// color
			{ _urb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ _lrb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ _llb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ _ulb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) }
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
			// f
			2,3,0,
			0,1,2,

			// b
			5,4,7,
			7,6,5,

			// t
			3, 7, 4,
			4, 0, 3,

			// b
			7,2,1,
			1,5,6,

			// l
			6,7,3,
			3,2,6,

			// r
			1,0,4,
			4,5,1
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

		// gameobject
		go = new GameObject("GameObject");
		add(go);

		// mesh
		Mesh* _mesh = new Mesh();
		_mesh->setVertices(_verts, _indices);

		// meshrenderer
		MeshRenderer* _mr = go->addComponent<MeshRenderer>();
		_mr->setMesh(_mesh);

		// material
		Material* _mat1 = new Material(new Shader("src/basic.shader"));
		_mr->setMaterial(_mat1);

		_camera = new GameObject("Camera");
		add(_camera);

		Camera* _cam = _camera->addComponent<Camera>();
		_cam->setPerspectiveCamera(45, 16.0f / 9.0f, 0.1f, 1000);
		_camera->getTransform()->setPosZ(-50);
		setActiveCamera(_cam);

		//Mesh* _mesh2 = new Mesh();
		//_mesh2->setVertices(_verts2, _indices);
		//go2 = new GameObject("GameObject");
		//MeshRenderer* _mr2 = go2->addComponent<MeshRenderer>();
		//_mr2->setMesh(_mesh2);
		//Material* _mat2 = new Material(new Shader("src/basic.shader"));
		//go->addChild(go2);
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

	Math::Vec2f mousePos;
	void TestScene::onRender(void)
	{
		Transform* _t = _camera->getTransform();
		const Math::Vec3f& _pos = _t->getPos();
		const Math::Vec3f& _euler = _t->getEuler();
		float _speed = 1;
		if (Input::getKey(KEY::A))
		{

			//_t->setEulerY(_euler.y + Time::getDeltaTime() * 10);
			_t->setPosX(_pos.x - Time::getDeltaTime()*_speed);
		}
		if (Input::getKey(KEY::D))
		{
			_t->setPosX(_pos.x + Time::getDeltaTime()*_speed);
		}
		if (Input::getKey(KEY::W))
		{
			_t->setPosZ(_pos.z + Time::getDeltaTime()*_speed);
		}
		if (Input::getKey(KEY::S))
		{
			_t->setPosZ(_pos.z - Time::getDeltaTime()*_speed);
		}
		if (Input::getKey(KEY::Q))
		{
			_t->setPosY(_pos.y - Time::getDeltaTime()*_speed);
		}
		if (Input::getKey(KEY::E))
		{
			_t->setPosY(_pos.y + Time::getDeltaTime()*_speed);
		}

		Math::Vec2f _delta = Input::getMousePosition() - mousePos;

		_t->setEulerY(_euler.y + _delta.x);

		mousePos = Input::getMousePosition();
		//v[11] = 1;
		
		//s->setUniform("mvp", p*v*m, false);
		//go->getComponent<MeshRenderer>()->getMaterial()->getShader()->setUniform("mvp", p*v*m, false);
		Scene::onRender();
	}
} // namespace gg
