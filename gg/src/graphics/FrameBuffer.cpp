#include "graphics/FrameBuffer.h"

#include "platform/opengl/GLCommon.h"

namespace gg { namespace graphics {
	FrameBuffer::FrameBuffer(void)
	{
	}

	FrameBuffer::~FrameBuffer(void)
	{
		GL(glDeleteFramebuffers(1, &m_ID));
	}

	void FrameBuffer::init(void)
	{
		if (m_IsInitialized)
		{
			GL(glDeleteFramebuffers(1, &m_ID));
		}
		GL(glGenFramebuffers(1, &m_ID));
		m_IsInitialized = true;
	}

	void FrameBuffer::bind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}
	void FrameBuffer::unbind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
}/*namespace graphics*/ } // namespace gg
