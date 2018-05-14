#include "graphics/RenderTarget.h"

#include "graphics/Texture.h"

namespace gg { namespace graphics {
	RenderTarget::RenderTarget(void)
	{
	}

	RenderTarget::~RenderTarget(void)
	{
		delete m_ColorTexture;
		delete m_DepthTexture;
		delete m_RenderBuffer;
	}

	void RenderTarget::init(uint width, uint height)
	{
		initColorTexture(width, height);
		initDepthTexture(width, height);
		m_FrameBuffer.init(width, height, m_ColorTexture, m_DepthTexture);
	}

	void RenderTarget::initColorTexture(uint width, uint height)
	{
		if (m_ColorTexture)
		{
			delete m_ColorTexture;
		}
		m_ColorTexture = new Texture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		m_ColorTexture->bind();
		m_ColorTexture->setFilterType(Texture::MinFilterType::Linear, Texture::MagFilterType::Linear);
		m_ColorTexture->setWrapType(Texture::WrapType::ClampToBorder);
		m_ColorTexture->unbind();
	}

	void RenderTarget::initDepthTexture(uint width, uint height)
	{
		if (m_DepthTexture)
		{
			delete m_DepthTexture;
		}
		m_DepthTexture = new Texture(width, height, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT);
		m_DepthTexture->bind();
		m_DepthTexture->setFilterType(Texture::MinFilterType::Linear, Texture::MagFilterType::Linear);
		m_DepthTexture->setWrapType(Texture::WrapType::ClampToBorder);
		m_DepthTexture->unbind();
	}

	void RenderTarget::initRenderBuffer(uint width, uint height)
	{
		// TODO: add code for adding RenderBuffers
		if (m_RenderBuffer)
		{
			delete m_RenderBuffer;
		}
	}

	void RenderTarget::bind(void) const
	{
		m_FrameBuffer.bind();
	}

	void RenderTarget::bindTextures(void) const
	{
		m_ColorTexture->bind(0);
		m_DepthTexture->bind(1);
	}

	void RenderTarget::unbind(void) const
	{
		m_FrameBuffer.unbind();
	}

	void RenderTarget::unbindTextures(void) const
	{
		// unbind any texture will do
		m_ColorTexture->unbind();
	}

	Texture* RenderTarget::getColorTexture(void) const
	{
		return m_ColorTexture;
	}

	Texture* RenderTarget::getDepthTexture(void) const
	{
		return m_DepthTexture;
	}


}/*namespace graphics*/ } // namespace gg
