#include "graphics/RenderBuffer.h"

#include "platform/opengl/GLCommon.h"

namespace gg { namespace graphics {
	RenderBuffer::RenderBuffer(void)
	{
	}

	RenderBuffer::~RenderBuffer(void)
	{
		GL(glDeleteRenderbuffers(1, &m_ID));
	}

	void RenderBuffer::init(float width, float height)
	{
		if (m_IsInitialized)
		{
			GL(glDeleteRenderbuffers(1, &m_ID));
		}
		GL(glGenRenderbuffers(1, &m_ID));

		bind();
			GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, width, height));
		unbind();
		m_IsInitialized = true;
	}

	void RenderBuffer::bind(void) const
	{
		GL(glBindRenderbuffer(GL_RENDERBUFFER, m_ID));
	}
	void RenderBuffer::unbind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}/*namespace graphics*/ } // namespace gg
