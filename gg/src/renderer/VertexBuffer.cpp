#include "renderer/VertexBuffer.h"

#include "GL/glew.h"
#include "platform/opengl/GLCommon.h"

namespace gg
{
	VertexBuffer::VertexBuffer(void)
	{ }
	VertexBuffer::VertexBuffer(const void* data, uint size)
	{
		GL(glGenBuffers(1, &m_ID));
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		m_IsInitialized = true;
	}
	VertexBuffer::~VertexBuffer(void)
	{
		GL(glDeleteBuffers(1, &m_ID));
	}
	void VertexBuffer::initData(const void* data, uint size)
	{
		if (m_IsInitialized) { return; }
		GL(glGenBuffers(1, &m_ID));
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
		GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		m_IsInitialized = true;
	}
	void VertexBuffer::bind(void) const
	{
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	}
	void VertexBuffer::unbind(void) const
	{
		GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
} // namespace gg
