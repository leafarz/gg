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

		delete m_ColorTexture;
		delete m_DepthTexture;
	}

	void FrameBuffer::init(uint width, uint height)
	{
		if (m_IsInitialized)
		{
			GL(glDeleteFramebuffers(1, &m_ID));
		}
		GL(glGenFramebuffers(1, &m_ID));
		m_IsInitialized = true;

		addColorTexture(width, height);
		addDepthTexture(width, height);

		GL(GLenum _status = glCheckFramebufferStatus(GL_FRAMEBUFFER));
		if (_status != GL_FRAMEBUFFER_COMPLETE)
		{
			ERROR("FrameBuffer status:" << _status);
			ASSERT(false);
		}
	}

	void FrameBuffer::addColorTexture(uint width, uint height)
	{
		if (!m_IsInitialized) { return; }
		if (m_ColorTexture)
		{
			delete m_ColorTexture;
		}
		m_ColorTexture = new Texture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		m_ColorTexture->bind();
		m_ColorTexture->setFilterType(Texture::MinFilterType::Linear, Texture::MagFilterType::Linear);
		m_ColorTexture->setWrapType(Texture::WrapType::ClampToBorder);
		m_ColorTexture->unbind();

		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
		GL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_ColorTexture->m_ID, 0));
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::addDepthTexture(uint width, uint height)
	{
		if (!m_IsInitialized) { return; }
		if (m_DepthTexture)
		{
			delete m_DepthTexture;
		}
		m_DepthTexture = new Texture(width, height, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);
		m_DepthTexture->bind();
		m_DepthTexture->setFilterType(Texture::MinFilterType::Linear, Texture::MagFilterType::Linear);
		m_DepthTexture->setWrapType(Texture::WrapType::ClampToBorder);
		m_DepthTexture->unbind();

		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
		GL(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_DepthTexture->m_ID, 0));
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	void FrameBuffer::addRenderBuffer(uint width, uint height)
	{
		if (!m_IsInitialized) { return; }
		// TODO: add code for adding RenderBuffers
	}

	void FrameBuffer::bind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, m_ID));
	}

	void FrameBuffer::bindColorTexture(uint samplerSlot) const
	{
		m_ColorTexture->bind(samplerSlot);
	}

	void FrameBuffer::bindDepthTexture(uint samplerSlot) const
	{
		m_DepthTexture->bind(samplerSlot);
	}

	void FrameBuffer::unbind(void) const
	{
		GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		GL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}/*namespace graphics*/ } // namespace gg
