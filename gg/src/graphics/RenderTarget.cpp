#include "graphics/RenderTarget.h"

#include "graphics/Texture.h"

namespace gg { namespace graphics {
	RenderTarget::RenderTarget(void)
	{
	}

	RenderTarget::~RenderTarget(void)
	{
	}

	void RenderTarget::init(uint width, uint height)
	{
		m_FrameBuffer.init(width, height);
	}

	void RenderTarget::bind(void) const
	{
		m_FrameBuffer.bind();
	}

	void RenderTarget::bindTextures(void) const
	{
		m_FrameBuffer.bindColorTexture(0);
		m_FrameBuffer.bindDepthTexture(1);
	}

	void RenderTarget::unbind(void) const
	{
		m_FrameBuffer.unbind();
	}


}/*namespace graphics*/ } // namespace gg
