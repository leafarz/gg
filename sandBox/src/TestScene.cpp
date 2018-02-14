#include "GL/glew.h"

#include "TestScene.h"

#include "core/Input.h"
#include "core/Time.h"

#include "core/gg.h"

#include "graphics/Shader.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"
#include "platform/opengl/GLCommon.h"

#include "entity/FreeCamera.h"
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

	GameObject *goCube, *goChair, *go2;
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
			{ _urb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 0.0, 0.0) },
			{ _lrb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 1.0, 0.0) },
			{ _llb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(0.0, 0.0, 1.0) },
			{ _ulb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 0.0, -1.0),	Color(1.0, 1.0, 1.0) }
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
			6,2,1,
			1,5,6,

			// l
			6,7,3,
			3,2,6,

			// r
			1,0,4,
			4,5,1
		};


		// ************* SHARED *************
		// shader
		Shader* _shader = new Shader("src/basic.shader");

		// material
		Material* _mat = new Material(_shader);

		// texture
		Texture *_tex = new Texture("src/Pikamannn.jpg");
		_mat->setTexture("test", _tex);

		// ************* CUBE *************
		// gameobject
		goCube = new GameObject("GameObject");
		add(goCube);

		// mesh
		Mesh* _cubeMesh = new Mesh();
		_cubeMesh->setVertices(_verts, _indices);

		// meshrenderer
		MeshRenderer* _mrCube = goCube->addComponent<MeshRenderer>();
		_mrCube->setMesh(_cubeMesh);
		_mrCube->setMaterial(_mat);

		// ************* CHAIR *************
		// gameobject
		goChair = new GameObject("Chair");
		add(goChair);
		goChair->getTransform()->setPos(2, 0, 0);
		goChair->getTransform()->setScale(0.01f, 0.01f, 0.01f);
		goChair->getTransform()->setEuler(-90, 90, 0);

		// mesh
		Mesh* _chairMesh = new Mesh("src/SM_Chair.FBX");

		// meshrenderer
		MeshRenderer* _mrChair = goChair->addComponent<MeshRenderer>();
		_mrChair->setMesh(_chairMesh);
		_mrChair->setMaterial(_mat);

		// ************* CAMERA *************
		FreeCamera* _freeCam = new FreeCamera(45, 16.0f / 9.0f, 0.1f, 1000);
		_freeCam->getTransform()->setPosZ(-10);
		add(_freeCam);
		setActiveCamera(_freeCam);

		//Mesh* _mesh2 = new Mesh();
		//_mesh2->setVertices(_verts2, _indices);
		//go2 = new GameObject("GameObject");
		//MeshRenderer* _mr2 = go2->addComponent<MeshRenderer>();
		//_mr2->setMesh(_mesh2);
		//Material* _mat2 = new Material(new Shader("src/basic.shader"));
		//go->addChild(go2);
		Scene::onInit();
	}
} // namespace gg
