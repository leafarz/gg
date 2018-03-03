#include "TestScene.h"
#include "core/gg.h"

namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	GameObject *goCube, *goTeapot, *goNano, *go2;
	bool rotateTeapot = false;
	Shader *teapotShader, *basicShader;
	Material* _cubeMat;
	void TestScene::onInit(void)
	{
		LightSettings.ambientColor.set(0.1f, 0.1f, 0.1f);

		//// spotlight
		//_cubeMat->setUniform("lights[0].color", Math::Vec4f(0, 1, 0, 1));
		//_cubeMat->setUniform("lights[0].position", Math::Vec4f(0, 1, 0, 1));
		////_cubeMat->setUniform("lights[0].position", Math::Vec4f(getActiveCamera()->getGameObject()->getTransform()->getPosition(),1));
		//_cubeMat->setUniform("lights[0].direction", Math::Vec3f(0, -1, -2).normal());
		////_cubeMat->setUniform("lights[0].direction", getActiveCamera()->getGameObject()->getTransform()->getForward());
		//_cubeMat->setUniformf("lights[0].angle", 20);

		//_cubeMat->setUniformf("lights[0].constantAttenuation", 0.002f);
		//_cubeMat->setUniformf("lights[0].linearAttenuation", 0.003f);
		//_cubeMat->setUniformf("lights[0].exponentAttenuation", 0.0001f);


		// pointlight
		//_cubeMat->setUniform("lights[1].color", Math::Vec4f(1, 0, 0, 1));
		//_cubeMat->setUniform("lights[1].position", Math::Vec4f(sin(Time::getCurrentTime()) * 2, 2, 0, 1));
		//_cubeMat->setUniformf("lights[1].constantAttenuation", 0.2f);
		//_cubeMat->setUniformf("lights[1].linearAttenuation", 0.1f);
		//_cubeMat->setUniformf("lights[1].exponentAttenuation", 0.2f);
		//_cubeMat->setUniformf("lights[1].angle", 180.0f);


		//// directionallight
		//_cubeMat->setUniform("lights[2].color", Math::Vec4f(0, 0, 0.5f, 1));
		//_cubeMat->setUniform("lights[2].position", Math::Vec4f(0, 0, 0, 0));
		//_cubeMat->setUniform("lights[2].direction", Math::Vec3f(-1, -1, 0).normal());

		// directional light
		Light *_dLight = new Light(Light::LightType::DirectionalLight);
		GameObject *_goDLight = new GameObject("DirectionalLight");
		_goDLight->addComponent(_dLight);
		_dLight->setColor(Color(1, 1, 1, 1));
		_dLight->getGameObject()->getTransform()->setPosition(0, 0, 0);
		_dLight->getGameObject()->getTransform()->lookAt(Math::Vec3f(-1, -1, 0).normal());
		//add(_goDLight);

		Light *_pLight = new Light(Light::LightType::PointLight);
		GameObject *_goPLight = new GameObject("PointLight");
		_goPLight->addComponent(_pLight);
		_pLight->setColor(Color(1, 1, 1, 1));
		_pLight->getGameObject()->getTransform()->setPosition(0, 2, 0);
		//_pLight->getGameObject()->getTransform()->setPosition(sin(Time::getCurrentTime()) * 2, 2, 0);
		_pLight->setAttenuation(0.2f, 0.1f, 0.2f);
		//add(_goPLight);

		Light *_sLight = new Light(Light::LightType::SpotLight);
		GameObject *_goSLight = new GameObject("SpotLight");
		_goSLight->addComponent(_sLight);
		_sLight->setColor(Color(0, 1, 0, 1));
		_sLight->getGameObject()->getTransform()->setPosition(0, 1, 0);
		// TODO: fix look at nan return value. *sqrt has negative
		_sLight->getGameObject()->getTransform()->lookAt(Math::Vec3f(0, -1, -2).normal());
		_sLight->setAttenuation(0.002f, 0.003f, 0.001f);
		_sLight->setAngle(20);
		add(_goSLight);


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
			{ _urf,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Color(1.0, 0.0, 0.0) }, // 00
			{ _urf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Color(1.0, 0.0, 0.0) }, // 01
			{ _urf,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Color(1.0, 0.0, 0.0) }, // 02

			{ _lrf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Color(0.0, 1.0, 0.0) }, // 03
			{ _lrf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Color(0.0, 1.0, 0.0) }, // 04
			{ _lrf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Color(0.0, 1.0, 0.0) }, // 05

			{ _llf,	Math::Vec2f(1.0, 0.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Color(0.0, 0.0, 1.0) }, // 06
			{ _llf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Color(0.0, 0.0, 1.0) }, // 07
			{ _llf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Color(0.0, 0.0, 1.0) }, // 08

			{ _ulf,	Math::Vec2f(1.0, 1.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Color(1.0, 1.0, 1.0) }, // 09
			{ _ulf,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Color(1.0, 1.0, 1.0) }, // 10
			{ _ulf,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  0.0, -1.0),	Color(1.0, 1.0, 1.0) }, // 11

			{ _urb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Color(1.0, 0.0, 0.0) }, // 12
			{ _urb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Color(1.0, 0.0, 0.0) }, // 13
			{ _urb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Color(1.0, 0.0, 0.0) }, // 14

			{ _lrb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 1.0,  0.0,  0.0),	Color(0.0, 1.0, 0.0) }, // 15
			{ _lrb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Color(0.0, 1.0, 0.0) }, // 16
			{ _lrb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Color(0.0, 1.0, 0.0) }, // 17

			{ _llb,	Math::Vec2f(0.0, 0.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Color(0.0, 0.0, 1.0) }, // 18
			{ _llb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0, -1.0,  0.0),	Color(0.0, 0.0, 1.0) }, // 19
			{ _llb,	Math::Vec2f(1.0, 0.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Color(0.0, 0.0, 1.0) }, // 20

			{ _ulb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f(-1.0,  0.0,  0.0),	Color(1.0, 1.0, 1.0) }, // 21
			{ _ulb,	Math::Vec2f(0.0, 1.0),	Math::Vec3f( 0.0,  1.0,  0.0),	Color(1.0, 1.0, 1.0) }, // 22
			{ _ulb,	Math::Vec2f(1.0, 1.0),	Math::Vec3f( 0.0,  0.0,  1.0),	Color(1.0, 1.0, 1.0) }, // 23
		};

		std::vector<Vertex> _quadVerts = 
		{
			{ Math::Vec3f(-0.5, 0.0, -0.5f),	Math::Vec2f(0.0, 0.0),	Math::Vec3f(0.0, 1.0, 0.0),		Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f( 0.5, 0.0, -0.5f),	Math::Vec2f(1.0, 0.0),	Math::Vec3f(0.0, 1.0, 0.0),		Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f(-0.5, 0.0,  0.5f),	Math::Vec2f(0.0, 1.0),	Math::Vec3f(0.0, 1.0, 0.0),		Color(1.0, 1.0, 1.0) },
			{ Math::Vec3f( 0.5, 0.0,  0.5f),	Math::Vec2f(1.0, 1.0),	Math::Vec3f(0.0, 1.0, 0.0),		Color(1.0, 1.0, 1.0) }
		};
		std::vector<uint> _quadIndices = 
		{
			0, 2, 3,
			3, 1, 0
		};

		std::vector<uint> _indices =
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

		// ************* CUBE *************
		// gameobject
		goCube = new GameObject("GameObject");
		// dont add
		add(goCube);
		//goCube->getTransform()->setPosition(-2, 0, 0);
		goCube->getTransform()->setScale(50, 1, 50);

		// mesh
		Mesh* _cubeMesh = new Mesh();
		_cubeMesh->setVertices(_quadVerts, _quadIndices, false);

		// shader, texture, material
		basicShader = new Shader("src/basic.shader");
		Texture *_tex = new Texture("src/Pikamannn.jpg");
		_cubeMat = new Material(basicShader);
		//_cubeMat->setTexture("test", _tex);

		// meshrenderer
		MeshRenderer* _mrCube = goCube->addComponent<MeshRenderer>();
		_mrCube->setMesh(_cubeMesh);
		_mrCube->setMaterial(_cubeMat);


		// ************* TEAPOT *************
		// gameobject
		goTeapot = new GameObject("Teapot");
		//add(goTeapot);
		goTeapot->getTransform()->setPosition(0, -1, 0);
		goTeapot->getTransform()->setScale(0.5f, 0.5f, 0.5f);

		// mesh
		Mesh* _teapotMesh = new Mesh("src/teapot.obj", true);

		// shader, texture, material
		teapotShader = new Shader("src/teapot.shader");
		Material* _teapotMat = new Material(teapotShader);

		// meshrenderer
		MeshRenderer* _mrTeapot = goTeapot->addComponent<MeshRenderer>();
		_mrTeapot->setMesh(_teapotMesh);
		_mrTeapot->setMaterial(_teapotMat);

		
		// ************* CAMERA *************
		FreeCamera* _freeCam = new FreeCamera(45, 16.0f / 9.0f, 0.1f, 1000);
		_freeCam->getTransform()->setPosition(0,2,-8);
		add(_freeCam);
		setActiveCamera(_freeCam);

		//Mesh* _mesh2 = new Mesh();
		//_mesh2->setVertices(_verts2, _indices);
		//go2 = new GameObject("GameObject");
		//MeshRenderer* _mr2 = go2->addComponent<MeshRenderer>();
		//_mr2->setMesh(_mesh2);
		//Material* _mat2 = new Material(new Shader("src/basic.shader"));
		//go->addChild(go2);
		
		// TODO: temporary. remove
		Log::removeLogLevel(LogLevel::Warn);
		Scene::onInit();
	}
	void TestScene::onUpdate(void)
	{
		if (Input::getKeyDown(KEY::G))
		{
			rotateTeapot = !rotateTeapot;
		}
		if (Input::getKeyDown(KEY::R))
		{
			//goTeapot->getTransform()->setEuler(0, 0, 0);
			//teapotShader->reload();
			basicShader->reload();
		}
		if (rotateTeapot)
		{
			goTeapot->getTransform()->addEulerY(static_cast<float>(Time::getDeltaTime()) * 30);
		}

		//// spotlight
		//_cubeMat->setUniform("lights[0].color", Math::Vec4f(0,1,0,1));
		//_cubeMat->setUniform("lights[0].position", Math::Vec4f(0, 1, 0, 1));
		////_cubeMat->setUniform("lights[0].position", Math::Vec4f(getActiveCamera()->getGameObject()->getTransform()->getPosition(),1));
		//_cubeMat->setUniform("lights[0].direction", Math::Vec3f(0,-1,-2).normal());
		////_cubeMat->setUniform("lights[0].direction", getActiveCamera()->getGameObject()->getTransform()->getForward());
		//_cubeMat->setUniformf("lights[0].angle", 20);

		//_cubeMat->setUniformf("lights[0].constantAttenuation", 0.002f);
		//_cubeMat->setUniformf("lights[0].linearAttenuation", 0.003f);
		//_cubeMat->setUniformf("lights[0].exponentAttenuation", 0.0001f);


		//// pointlight
		//_cubeMat->setUniform("lights[1].color", Math::Vec4f(1, 0, 0, 1));
		//_cubeMat->setUniform("lights[1].position", Math::Vec4f(sin(Time::getCurrentTime()) * 2, 2, 0, 1));
		//_cubeMat->setUniformf("lights[1].constantAttenuation", 0.2f);
		//_cubeMat->setUniformf("lights[1].linearAttenuation", 0.1f);
		//_cubeMat->setUniformf("lights[1].exponentAttenuation", 0.2f);
		//_cubeMat->setUniformf("lights[1].angle", 180.0f);


		//// directionallight
		//_cubeMat->setUniform("lights[2].color", Math::Vec4f(0, 0, 0.5f, 1));
		//_cubeMat->setUniform("lights[2].position", Math::Vec4f(0,0,0,0));
		//_cubeMat->setUniform("lights[2].direction", Math::Vec3f(-1,-1,0).normal());

		Scene::onUpdate();
	}
} // namespace gg
