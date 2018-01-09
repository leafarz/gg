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
#include "debug/Log.h"
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
		//glGenBuffers(1, &vao);
		//glBindVertexArray(vao);
		//	vb.bind();

		//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		//	glEnableVertexAttribArray(0);

		//	glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glBindVertexArray(0);
		
		Shader *s = new Shader("src/basic.shader");
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
		if (Input::getKey(KEY::A))
		{
			//LOG(Time::getCurrentTime() << ":onUpdate");

			va.bind();
			ib.bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}
} // namespace gg
