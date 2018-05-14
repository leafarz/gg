#include "graphics/FrameBuffer.h"

#include "platform/opengl/GLCommon.h"

#include "debug/Log.h"

#include "graphics/Texture.h"
#include "graphics/RenderBuffer.h"

namespace gg { namespace graphics {
	FrameBuffer::FrameBuffer(void)
	{
	}

	FrameBuffer::~FrameBuffer(void)
	{
		GL(glDeleteFramebuffers(1, &m_ID));
	}

	void FrameBuffer::init(uint width, uint height, Texture* colorTexture, Texture* depthTexture)
	{
		if (m_IsInitialized)
		{
			GL(glDeleteFramebuffers(1, &m_ID));
		}
		GL(glGenFramebuffers(1, &m_ID));
		m_IsInitialized = true;

		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
			GL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTexture->m_ID, 0));
			GL(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture->m_ID, 0));
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		GL(GLenum _status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (_status != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR("FrameBuffer status:" << _status);
			ASSERT(false);
		}
	}

	void FrameBuffer::bind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}

	void FrameBuffer::unbind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}/*namespace graphics*/ } // namespace gg
