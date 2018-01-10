#include "renderer/IndexBuffer.h"

#include "GL/glew.h"
#include "platform/opengl/GLCommon.h"

namespace gg
{
	IndexBuffer::IndexBuffer(void)
		: m_Count(0)
	{ }
	IndexBuffer::IndexBuffer(const uint *data, uint count)
		: m_Count(count)
	{
		GL(glGenBuffers(1, &m_ID));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
		m_IsInitialized = true;
	}
	IndexBuffer::~IndexBuffer(void)
	{
		GL(glDeleteBuffers(1, &m_ID));
	}
	void IndexBuffer::initData(const uint * data, uint count)
	{
		if (m_IsInitialized) { return; }
		GL(glGenBuffers(1, &m_ID));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
		GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
		m_Count = count;
		m_IsInitialized = true;
	}
	void IndexBuffer::bind(void) const
	{
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}
	void IndexBuffer::unbind(void) const
	{
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
} // namespace gg
