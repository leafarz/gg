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

	void RenderBuffer::bind(void) const
	{
		GL(glBindRenderbuffer(GL_RENDERBUFFER, m_ID));
	}
	void RenderBuffer::unbind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}/*namespace graphics*/ } // namespace gg
