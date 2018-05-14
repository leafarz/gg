#include "TestScene.h"
#include "core/gg.h"
#include "debug/DebugUtils.h"

#include "util/Iterators.h"
#include <sstream>

#include "graphics/RenderTarget.h"

namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	GameObject *go1, *go2, *go3;
	GameObject *goDLight, *goSLight, *goPLight;
	graphics::Shader *basicShader, *mirrorShader;
	Light *dLight, *sLight;
	graphics::RenderTarget* m_RenderTarget;

	FreeCamera *m_FreeCamera1, *m_FreeCamera2;
	void TestScene::onInit(void)
	{
		LightSettings.ambientColor.set(0.1f, 0.1f, 0.1f);

		// directional light
		dLight = new Light(Light::LightType::DirectionalLight);
		goDLight = new GameObject("DirectionalLight");
		goDLight->addComponent(dLight);
		dLight->setColor(math::Color(1.0f, 1.0f, 1.0f, 1));
		dLight->setIntensity(1);
		dLight->getGameObject()->getTransform()->setPosition(0, 3, 0);
		dLight->getGameObject()->getTransform()->lookAt(math::Vec3f(-1, -1, 0).normal());
		add(goDLight);

		//Light *_pLight = new Light(Light::LightType::PointLight);
		//goPLight = new GameObject("PointLight");
		//goPLight->addComponent(_pLight);
		//_pLight->setColor(math::Color(1, 1, 1, 1));
		//_pLight->getGameObject()->getTransform()->setPosition(0, 2, 0);
		//_pLight->setAttenuation(0.2f, 0.2f, 0.2f);
		//add(goPLight);

		sLight = new Light(Light::LightType::SpotLight);
		goSLight = new GameObject("SpotLight");
		goSLight->addComponent(sLight);
		sLight->setColor(math::Color(0, 1, 0, 1));
		sLight->getGameObject()->getTransform()->setPosition(4, 2, 0);
		sLight->getGameObject()->getTransform()->lookAt(math::Vec3f(-1, 0, 0).normal());
		sLight->setAttenuation(0.002f, 0.003f, 0.001f);
		sLight->setAngle(20);
		add(goSLight);


		math::Vec3f _ulf = math::Vec3f(-0.5f,  0.5f, -0.5);
		math::Vec3f _urf = math::Vec3f( 0.5f,  0.5f, -0.5);
		math::Vec3f _llf = math::Vec3f(-0.5f, -0.5f, -0.5);
		math::Vec3f _lrf = math::Vec3f( 0.5f, -0.5f, -0.5);

		math::Vec3f _ulb = math::Vec3f(-0.5f,  0.5f, 0.5);
		math::Vec3f _urb = math::Vec3f( 0.5f,  0.5f, 0.5);
		math::Vec3f _llb = math::Vec3f(-0.5f, -0.5f, 0.5);
		math::Vec3f _lrb = math::Vec3f( 0.5f, -0.5f, 0.5);

		std::vector<graphics::Vertex> _cubeVerts =
		{
			// pos	// uv					// normal						// color
			{ _urf,	math::Vec2f(0.0, 1.0),	math::Vec3f( 1.0,  0.0,  0.0),	math::Color(1.0, 0.0, 0.0) }, // 00
			{ _urf,	math::Vec2f(1.0, 0.0),	math::Vec3f( 0.0,  1.0,  0.0),	math::Color(1.0, 0.0, 0.0) }, // 01
			{ _urf,	math::Vec2f(1.0, 1.0),	math::Vec3f( 0.0,  0.0, -1.0),	math::Color(1.0, 0.0, 0.0) }, // 02

			{ _lrf,	math::Vec2f(0.0, 0.0),	math::Vec3f( 1.0,  0.0,  0.0),	math::Color(0.0, 1.0, 0.0) }, // 03
			{ _lrf,	math::Vec2f(1.0, 0.0),	math::Vec3f( 0.0, -1.0,  0.0),	math::Color(0.0, 1.0, 0.0) }, // 04
			{ _lrf,	math::Vec2f(1.0, 0.0),	math::Vec3f( 0.0,  0.0, -1.0),	math::Color(0.0, 1.0, 0.0) }, // 05

			{ _llf,	math::Vec2f(1.0, 0.0),	math::Vec3f(-1.0,  0.0,  0.0),	math::Color(0.0, 0.0, 1.0) }, // 06
			{ _llf,	math::Vec2f(0.0, 0.0),	math::Vec3f( 0.0, -1.0,  0.0),	math::Color(0.0, 0.0, 1.0) }, // 07
			{ _llf,	math::Vec2f(0.0, 0.0),	math::Vec3f( 0.0,  0.0, -1.0),	math::Color(0.0, 0.0, 1.0) }, // 08

			{ _ulf,	math::Vec2f(1.0, 1.0),	math::Vec3f(-1.0,  0.0,  0.0),	math::Color(1.0, 1.0, 1.0) }, // 09
			{ _ulf,	math::Vec2f(0.0, 0.0),	math::Vec3f( 0.0,  1.0,  0.0),	math::Color(1.0, 1.0, 1.0) }, // 10
			{ _ulf,	math::Vec2f(0.0, 1.0),	math::Vec3f( 0.0,  0.0, -1.0),	math::Color(1.0, 1.0, 1.0) }, // 11

			{ _urb,	math::Vec2f(1.0, 1.0),	math::Vec3f( 1.0,  0.0,  0.0),	math::Color(1.0, 0.0, 0.0) }, // 12
			{ _urb,	math::Vec2f(1.0, 1.0),	math::Vec3f( 0.0,  1.0,  0.0),	math::Color(1.0, 0.0, 0.0) }, // 13
			{ _urb,	math::Vec2f(0.0, 1.0),	math::Vec3f( 0.0,  0.0,  1.0),	math::Color(1.0, 0.0, 0.0) }, // 14

			{ _lrb,	math::Vec2f(1.0, 0.0),	math::Vec3f( 1.0,  0.0,  0.0),	math::Color(0.0, 1.0, 0.0) }, // 15
			{ _lrb,	math::Vec2f(1.0, 1.0),	math::Vec3f( 0.0, -1.0,  0.0),	math::Color(0.0, 1.0, 0.0) }, // 16
			{ _lrb,	math::Vec2f(0.0, 0.0),	math::Vec3f( 0.0,  0.0,  1.0),	math::Color(0.0, 1.0, 0.0) }, // 17

			{ _llb,	math::Vec2f(0.0, 0.0),	math::Vec3f(-1.0,  0.0,  0.0),	math::Color(0.0, 0.0, 1.0) }, // 18
			{ _llb,	math::Vec2f(0.0, 1.0),	math::Vec3f( 0.0, -1.0,  0.0),	math::Color(0.0, 0.0, 1.0) }, // 19
			{ _llb,	math::Vec2f(1.0, 0.0),	math::Vec3f( 0.0,  0.0,  1.0),	math::Color(0.0, 0.0, 1.0) }, // 20

			{ _ulb,	math::Vec2f(0.0, 1.0),	math::Vec3f(-1.0,  0.0,  0.0),	math::Color(1.0, 1.0, 1.0) }, // 21
			{ _ulb,	math::Vec2f(0.0, 1.0),	math::Vec3f( 0.0,  1.0,  0.0),	math::Color(1.0, 1.0, 1.0) }, // 22
			{ _ulb,	math::Vec2f(1.0, 1.0),	math::Vec3f( 0.0,  0.0,  1.0),	math::Color(1.0, 1.0, 1.0) }, // 23
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
			{ math::Vec3f(-0.5, 0.0, -0.5f),	math::Vec2f(0.0, 0.0),	math::Vec3f(0.0, 1.0, 0.0),		math::Color(1.0, 1.0, 1.0) },
			{ math::Vec3f( 0.5, 0.0, -0.5f),	math::Vec2f(1.0, 0.0),	math::Vec3f(0.0, 1.0, 0.0),		math::Color(1.0, 1.0, 1.0) },
			{ math::Vec3f(-0.5, 0.0,  0.5f),	math::Vec2f(0.0, 1.0),	math::Vec3f(0.0, 1.0, 0.0),		math::Color(1.0, 1.0, 1.0) },
			{ math::Vec3f( 0.5, 0.0,  0.5f),	math::Vec2f(1.0, 1.0),	math::Vec3f(0.0, 1.0, 0.0),		math::Color(1.0, 1.0, 1.0) }
		};
		std::vector<uint> _quadIndices = 
		{
			0, 2, 3,
			3, 1, 0
		};

		m_RenderTarget = new graphics::RenderTarget();
		m_RenderTarget->init(1280, 720);

		// ************* SHARED *************
		basicShader = new graphics::Shader("src/basic.shader");
		mirrorShader = new graphics::Shader("src/mirror.shader");

		graphics::Material* _basicMat;
		_basicMat = new graphics::Material(basicShader);

		graphics::Material* _mirrorMat;
		_mirrorMat = new graphics::Material(mirrorShader);

		// mesh
		graphics::Mesh* _cubeMesh = new graphics::Mesh();
		_cubeMesh->setVertices(_cubeVerts, _cubeIndices, false);

		graphics::Mesh* _quadMesh = new graphics::Mesh();
		_quadMesh->setVertices(_quadVerts, _quadIndices, false);

		graphics::Mesh* _teapotMesh = new graphics::Mesh("src/teapot.obj", true);

		// texture
		graphics::Texture *_tex = new graphics::Texture("src/Pikamannn.jpg");
		_tex->setFilterType(graphics::Texture::MinFilterType::Linear, graphics::Texture::MagFilterType::Linear);
		_tex->setWrapType(graphics::Texture::WrapType::ClampToBorder);


		// ************* GAMEOBJECT1 *************
		// gameobject
		go1 = new GameObject("Cube");
		add(go1);
		go1->getTransform()->setScale(0.5f, 0.5f, 0.5f);
		// meshrenderer
		MeshRenderer* _mrTeapot = go1->addComponent<MeshRenderer>();
		_mrTeapot->setMesh(_teapotMesh);
		_mrTeapot->setMaterial(_basicMat);


		// ************* GAMEOBJECT2 *************
		// gameobject
		go2 = new GameObject("Cube2");
		add(go2);
		go2->getTransform()->setPosition(0.5, 0.5, 0.5);
		go2->getTransform()->setScale(50, 0.01f, 50);
		// meshrenderer
		MeshRenderer* _mrFloor = go2->addComponent<MeshRenderer>();
		_mrFloor->setMesh(_cubeMesh);
		_mrFloor->setMaterial(_basicMat);


		//// ************* GAMEOBJECT3 *************
		go3 = new GameObject("Renderer");
		add(go3);
		go3->getTransform()->setPosition(0, 2, -4);
		go3->getTransform()->setEuler(-90,0,0);
		go3->getTransform()->setScale(3 * 16.0f/9.0f, 3, 3);
		// meshrenderer
		MeshRenderer* _mrQuad = go3->addComponent<MeshRenderer>();
		_mrQuad->setMesh(_quadMesh);
		_mrQuad->setMaterial(_mirrorMat);
		_mirrorMat->setTexture("sys", m_RenderTarget);



		// ************* CAMERA *************
		m_FreeCamera1 = new FreeCamera(45, 16.0f / 9.0f, 0.1f, 100);
		m_FreeCamera1->getTransform()->setPosition(0,2,-8);
		m_FreeCamera1->setMoveSpeed(0.05f);
		add(m_FreeCamera1);
		setActiveCamera(m_FreeCamera1);

		m_FreeCamera2 = new FreeCamera(45, 16.0f / 9.0f, 0.1f, 100);
		m_FreeCamera2->getTransform()->setPosition(-6, 2, 0);
		m_FreeCamera2->getTransform()->lookAt(math::Vec3f::right);
		m_FreeCamera2->setMoveSpeed(0.05f);
		add(m_FreeCamera2);
		
		Scene::onInit();
	}

	
	float dLightColor[3] = { 1,1,1 };
	float dLightLookAt[3] = { -1,-2,1.5f };
	float dLightIntensity = 1;
	float dLightSpecular = 32;

	float sLightPosition[3] = { 4,2,0 };
	float sLightColor[3] = { 0,1,0 };
	float sLightAttenuation[3] = { 0.002f, 0.003f, 0.001f };
	float sLightLookAt[3] = { -1, 0, 0 };
	float sLightIntensity = 1;
	float sLightSpecular = 32;
	float sLightAngle = 20;

	float position[3] = { 0,1,0 };
	float lookAt[3] = { 0,0,1 };
	float scale[3] = { 0.5,0.5,0.5 };

	float precision = 1;

	void TestScene::onUpdate(void)
	{
		Scene::onUpdate();
		if (Input::getKeyDown(KEY::R))
		{
			basicShader->reload();
		}

		if (Input::getKeyDown(KEY::ALPHA1))
		{
			setActiveCamera(m_FreeCamera1);
		}
		if (Input::getKeyDown(KEY::ALPHA2))
		{
			setActiveCamera(m_FreeCamera2);
		}

		m_FreeCamera2->getCamera()->render(m_RenderTarget);


		// ------------
		ImGui::Text("[World]");
		ImGui::Checkbox("Grid", &m_ShowGrid);
		math::Vec3f _cameraPos = getActiveCamera()->getGameObject()->getTransform()->getPosition();
		std::stringstream stream;
		stream << getActiveCamera()->getGameObject()->getTransform()->getPosition();
		ImGui::Text(stream.str().c_str());

		if (m_ShowGrid) { drawGrid(20); }

		ImGui::Text("\n[Directional Light]");

		ImGui::InputFloat3("[D]Look At", dLightLookAt);
		goDLight->getTransform()->lookAt(math::Vec3f(dLightLookAt).normal());

		ImGui::SliderFloat("[D]Intensity", &dLightIntensity, 0, 2);
		dLight->setIntensity(dLightIntensity);

		ImGui::ColorEdit3("[D]Color", dLightColor);
		dLight->setColor(math::Color(dLightColor[0], dLightColor[1], dLightColor[2]));

		ImGui::SliderFloat("[D]Specular", &dLightSpecular, 0, 256);
		dLight->setSpecular(dLightSpecular);



		ImGui::Text("\n[SpotLight]");
		ImGui::DragFloat3("[S]Position", sLightPosition, 0.5, -10, 10);
		goSLight->getTransform()->setPosition(sLightPosition);

		ImGui::InputFloat3("[S]Look At", sLightLookAt);
		goSLight->getTransform()->lookAt(math::Vec3f(sLightLookAt).normal());

		ImGui::SliderFloat("[S]Intensity", &sLightIntensity, 0, 2);
		sLight->setIntensity(sLightIntensity);

		ImGui::ColorEdit3("[S]Color", sLightColor);
		sLight->setColor(math::Color(sLightColor[0], sLightColor[1], sLightColor[2]));

		ImGui::SliderFloat("[S]Specular", &sLightSpecular, 0, 256);
		sLight->setSpecular(sLightSpecular);

		ImGui::InputFloat3("[S]Attenuation", sLightAttenuation);
		sLight->setAttenuation(sLightAttenuation[0], sLightAttenuation[1], sLightAttenuation[2]);

		ImGui::SliderFloat("[S]Angle", &sLightAngle, 0, 89.99f);
		sLight->setAngle(sLightAngle);



		ImGui::Text("\n[Box]");
		ImGui::DragFloat3("Position", position, 0.1f, -10, 10);
		math::Vec3f _position = math::Vec3f(position);

		ImGui::DragFloat3("LookAt", lookAt, 0.1f, -1, 1);
		math::Vec3f _lookAt = math::Vec3f(lookAt).normal();

		ImGui::DragFloat3("Scale", scale, 0.1f, -10, 10);
		math::Vec3f _scale = math::Vec3f(scale);

		go1->getTransform()->setPosition(_position);
		go1->getTransform()->lookAt(_lookAt);
		go1->getTransform()->setScale(_scale);

		drawLightLocations();

		// draw camera frustum
		debug::drawCameraFrustum(m_FreeCamera1->getCamera(), math::Color::green);
		debug::drawCameraFrustum(m_FreeCamera2->getCamera(), math::Color::blue);

	}

	void TestScene::drawLightLocations(void)
	{
		// directional light
		const Transform* _tDLight = goDLight->getTransform();
		const math::Vec3f& _posDLight = _tDLight->getPosition();
		const math::Vec3f _fDLight = _tDLight->getForward();
		debug::drawWireCube(_posDLight, 0.2f, _tDLight->getRotation(), math::Color::yellow);
		debug::drawLine(_posDLight, _posDLight + _fDLight);

		// spotlight
		const Transform* _tSLight = goSLight->getTransform();
		const math::Vec3f& _posSLight = _tSLight->getPosition();
		const math::Vec3f _fSLight = _tSLight->getForward();
		debug::drawWireCube(_posSLight, 0.2f, _tSLight->getRotation(), math::Color::yellow);
		debug::drawLine(_posSLight, _posSLight + _fSLight);
	}

	void TestScene::drawGrid(int length)
	{
		FOR(i, -length, length + 1)
		{
			debug::drawLine(math::Vec3f((float)(-length), 0, (float)i), math::Vec3f((float)length, 0, (float)i), math::Color::gray);
		}
		FOR(i, -length, length + 1)
		{
			debug::drawLine(math::Vec3f(i, 0, -length), math::Vec3f(i, 0, length), math::Color::gray);
		}

		debug::drawLine(math::Vec3f::zero, math::Vec3f::forward, 5, math::Color::blue);
		debug::drawLine(math::Vec3f::zero, math::Vec3f::up, 5, math::Color::green);
		debug::drawLine(math::Vec3f::zero, math::Vec3f::right, 5, math::Color::red);
	}
} // namespace gg
