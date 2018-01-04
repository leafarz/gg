#include "GL/glew.h"

#include "TestScene.h"
#include "core/Input.h"
#include "core/Time.h"

#include "core/gg.h"

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
	GLuint vao, vbo, ibo;
	void TestScene::onInit(void)
	{
		GLfloat _pos[9] =
		{
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
		};

		glGenBuffers(1, &vao);
		glGenBuffers(1, &vbo);

		glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(_pos), _pos, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		
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

			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 5);
			glBindVertexArray(0);
		}
	}
} // namespace gg
