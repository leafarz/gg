#include "GL/glew.h"

#include "TestScene.h"

#include "core/Input.h"
#include "core/Time.h"

#include "core/gg.h"

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"

#include "platform/opengl/GLCommon.h"

namespace gg
{
	TestScene::TestScene(void)
	{
	}

	TestScene::~TestScene(void)
	{
	}

	// TODO: sample code. delete after.
	VertexArray va;
	IndexBuffer ib;
	VertexBuffer vb;
	Shader *s;
	void TestScene::onInit(void)
	{
		//TODO: test on x,y only
		float _pos[] = {
			// pos			// color
			 0.5f,  0.5f,	1.0, 0.0, 0.0,
			 0.5f, -0.5f,	0.0, 1.0, 0.0,
			-0.5f, -0.5f,	0.0, 0.0, 1.0,
			-0.5f,  0.5f,	1.0, 1.0, 1.0
		};
		uint _indices[6] =
		{
			0, 1, 3,
			1, 2, 3
		};

		vb.initData(_pos, sizeof(_pos));
		ib.initData(_indices, sizeof(_indices) / sizeof(uint));

		VertexBufferLayout _layout = VertexBufferLayout();
		_layout.Push<float>(2);
		_layout.Push<float>(3);

		va.init();
		va.addBuffer(vb, _layout);
		
		s = new Shader("src/basic.shader");
		s->bind();

		va.unbind();
		s->unbind();
		vb.unbind();
		ib.unbind();
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

		if (Input::getKey(KEY::A))
		{
			// watch for order
			va.bind();
			ib.bind();
			s->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}
} // namespace gg
