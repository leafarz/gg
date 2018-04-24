#include "TestScene.h"
#include "core/gg.h"
#include "debug/DebugUtils.h"

#include "util/Iterators.h"

namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	GameObject *go1, *go2;
	GameObject *goDLight, *goSLight, *goPLight;
	graphics::Shader *basicShader;

	void TestScene::onInit(void)
	{
		LightSettings.ambientColor.set(0.1f, 0.1f, 0.1f);

		// directional light
		Light *_dLight = new Light(Light::LightType::DirectionalLight);
		goDLight = new GameObject("DirectionalLight");
		goDLight->addComponent(_dLight);
		_dLight->setColor(Math::Color(1.0f, 1.0f, 1.0f, 1));
		_dLight->setIntensity(1);
		_dLight->getGameObject()->getTransform()->setPosition(0, 0, 0);
		_dLight->getGameObject()->getTransform()->lookAt(Math::Vec3f(-1, -1, 0).normal());
		add(goDLight);

		//Light *_pLight = new Light(Light::LightType::PointLight);
		//goPLight = new GameObject("PointLight");
		//goPLight->addComponent(_pLight);
		//_pLight->setColor(Math::Color(1, 1, 1, 1));
		//_pLight->getGameObject()->getTransform()->setPosition(0, 2, 0);
		//_pLight->setAttenuation(0.2f, 0.2f, 0.2f);
		//add(goPLight);

		//Light *_sLight = new Light(Light::LightType::SpotLight);
		//goSLight = new GameObject("SpotLight");
		//goSLight->addComponent(_sLight);
		//_sLight->setColor(Math::Color(0, 1, 0, 1));
		//_sLight->getGameObject()->getTransform()->setPosition(0, 1, 0);
		//_sLight->getGameObject()->getTransform()->lookAt(Math::Vec3f(0, -1, -2).normal());
		//_sLight->setAttenuation(0.002f, 0.003f, 0.001f);
		//_sLight->setAngle(20);
		//add(goSLight);


		Math::Vec3f _ulf = Math::Vec3f(-0.5f,  0.5f, -0.5);
		Math::Vec3f _urf = Math::Vec3f( 0.5f,  0.5f, -0.5);
		Math::Vec3f _llf = Math::Vec3f(-0.5f, -0.5f, -0.5);
		Math::Vec3f _lrf = Math::Vec3f( 0.5f, -0.5f, -0.5);

		Math::Vec3f _ulb = Math::Vec3f(-0.5f,  0.5f, 0.5);
		Math::Vec3f _urb = Math::Vec3f( 0.5f,  0.5f, 0.5);
		Math::Vec3f _llb = Math::Vec3f(-0.5f, -0.5f, 0.5);
		Math::Vec3f _lrb = Math::Vec3f( 0.5f, -0.5f, 0.5);

		std::vector<graphics::Vertex> _cubeVerts =
		{
			// pos	// uv					// normal						// color
			{ _urf,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Math::Color(1.0, 0.0, 0.0) }, // 00
			{ _urf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Math::Color(1.0, 0.0, 0.0) }, // 01
			{ _urf,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Math::Color(1.0, 0.0, 0.0) }, // 02

			{ _lrf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Math::Color(0.0, 1.0, 0.0) }, // 03
			{ _lrf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Math::Color(0.0, 1.0, 0.0) }, // 04
			{ _lrf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Math::Color(0.0, 1.0, 0.0) }, // 05

			{ _llf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Math::Color(0.0, 0.0, 1.0) }, // 06
			{ _llf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Math::Color(0.0, 0.0, 1.0) }, // 07
			{ _llf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Math::Color(0.0, 0.0, 1.0) }, // 08

			{ _ulf,	Math::Vec2f(1.0, 1.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Math::Color(1.0, 1.0, 1.0) }, // 09
			{ _ulf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Math::Color(1.0, 1.0, 1.0) }, // 10
			{ _ulf,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Math::Color(1.0, 1.0, 1.0) }, // 11

			{ _urb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Math::Color(1.0, 0.0, 0.0) }, // 12
			{ _urb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Math::Color(1.0, 0.0, 0.0) }, // 13
			{ _urb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Math::Color(1.0, 0.0, 0.0) }, // 14

			{ _lrb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Math::Color(0.0, 1.0, 0.0) }, // 15
			{ _lrb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Math::Color(0.0, 1.0, 0.0) }, // 16
			{ _lrb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Math::Color(0.0, 1.0, 0.0) }, // 17

			{ _llb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Math::Color(0.0, 0.0, 1.0) }, // 18
			{ _llb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Math::Color(0.0, 0.0, 1.0) }, // 19
			{ _llb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Math::Color(0.0, 0.0, 1.0) }, // 20

			{ _ulb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Math::Color(1.0, 1.0, 1.0) }, // 21
			{ _ulb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Math::Color(1.0, 1.0, 1.0) }, // 22
			{ _ulb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Math::Color(1.0, 1.0, 1.0) }, // 23
		};
		std::vector<uint> _cubeIndices =
		{
			// front
			2,5,8,
			8,11,2,

			// back
			23,20,17,
			17,14,23,

			// top
			13,1,10,
			10,22,13,

			// bottom
			4,16,19,
			19,7,4,

			// left
			9,6,18,
			18,21,9,

			// right
			12,15,3,
			3,0,12
		};

		std::vector<graphics::Vertex> _quadVerts =
		{
			{ Math::Vec3f(-0.5, 0.0, -0.5f),	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 1.0, 0.0),		Math::Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f( 0.5, 0.0, -0.5f),	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 1.0, 0.0),		Math::Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f(-0.5, 0.0,  0.5f),	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 1.0, 0.0),		Math::Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f( 0.5, 0.0,  0.5f),	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 1.0, 0.0),		Math::Color(1.0, 1.0, 1.0) }
		};
		std::vector<uint> _quadIndices = 
		{
			0, 2, 3,
			3, 1, 0
		};

		// ************* SHARED *************
		basicShader = new graphics::Shader("src/basic.shader");

		graphics::Material* _basicMat;
		_basicMat = new graphics::Material(basicShader);

		// mesh
		graphics::Mesh* _cubeMesh = new graphics::Mesh();
		_cubeMesh->setVertices(_cubeVerts, _cubeIndices, false);

		graphics::Mesh* _quadMesh = new graphics::Mesh();
		_cubeMesh->setVertices(_quadVerts, _quadIndices, false);

		graphics::Mesh* _teapotMesh = new graphics::Mesh("src/teapot.obj", true);

		// texture
		graphics::Texture *_tex = new graphics::Texture("src/Pikamannn.jpg");


		// ************* GAMEOBJECT1 *************
		// gameobject
		go1 = new GameObject("Cube");
		add(go1);

		// meshrenderer
		MeshRenderer* _mrCube = go1->addComponent<MeshRenderer>();
		_mrCube->setMesh(_cubeMesh);
		_mrCube->setMaterial(_basicMat);


		// ************* GAMEOBJECT2 *************
		// gameobject
		go2 = new GameObject("Cube2");
		add(go2);
		go2->getTransform()->setPosition(0, 0, 0);
		go2->getTransform()->setScale(0.5f, 0.5f, 0.5f);

		// meshrenderer
		MeshRenderer* _mrTeapot = go2->addComponent<MeshRenderer>();
		_mrTeapot->setMesh(_cubeMesh);
		_mrTeapot->setMaterial(_basicMat);


		// ************* CAMERA *************
		FreeCamera* _freeCam = new FreeCamera(45, 16.0f / 9.0f, 0.1f, 1000);
		_freeCam->getTransform()->setPosition(0,2,-8);
		_freeCam->setMoveSpeed(0.05);
		add(_freeCam);
		setActiveCamera(_freeCam);
		
		Scene::onInit();
	}

	float position[3] = { 0,1,0 };
	float lookAt[3] = { 0,0,1 };
	float scale[3] = { 1,1,1 };
	void TestScene::onUpdate(void)
	{
		if (Input::getKeyDown(KEY::R))
		{
			basicShader->reload();
		}


		// ------------

		ImGui::Checkbox("Grid", &m_ShowGrid);
		if (m_ShowGrid) { drawGrid(20); }

		ImGui::InputFloat3("Position", position);
		Math::Vec3f _position = Math::Vec3f(position);

		ImGui::InputFloat3("LookAt", lookAt);
		Math::Vec3f _lookAt = Math::Vec3f(lookAt).normal();

		ImGui::InputFloat3("Scale", scale);
		Math::Vec3f _scale = Math::Vec3f(scale);

		debug::drawLine(_position, _position + _lookAt);
		go1->getTransform()->setPosition(_position);
		go1->getTransform()->lookAt(_lookAt);
		go1->getTransform()->setScale(_scale);

		Scene::onUpdate();
	}

	void TestScene::drawGrid(int length)
	{
		FOR(i, -length, length + 1)
		{
			debug::drawLine(Math::Vec3f(-length, 0, i), Math::Vec3f(length, 0, i), Math::Color::gray);
		}
		FOR(i, -length, length + 1)
		{
			debug::drawLine(Math::Vec3f(i, 0, -length), Math::Vec3f(i, 0, length), Math::Color::gray);
		}

		debug::drawLine(Math::Vec3f::zero, Math::Vec3f::forward, 5, Math::Color::blue);
		debug::drawLine(Math::Vec3f::zero, Math::Vec3f::up, 5, Math::Color::green);
		debug::drawLine(Math::Vec3f::zero, Math::Vec3f::right, 5, Math::Color::red);
	}
} // namespace gg
