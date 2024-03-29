#ifndef		GG_RENDERTARGET_H
#define		GG_RENDERTARGET_H
#pragma once

#include "core/Types.h"

#include "graphics/FrameBuffer.h"

namespace gg { namespace graphics { class Texture; class RenderBuffer; } }

namespace gg { namespace graphics {
	class RenderTarget
	{
	private:
		friend class Material;
		friend class Renderer;

	public:
		RenderTarget(void);
		~RenderTarget(void);

		void init(uint width, uint height);

	private:
		inline Texture* getColorTexture(void) const { return m_ColorTexture; }
		inline Texture* getDepthTexture(void) const { return m_DepthTexture; }

		void initColorTexture(uint width, uint height);
		void initDepthTexture(uint width, uint height);
		void initRenderBuffer(uint width, uint height);

		void bind(void) const;
		void bindTextures(void) const;
		void unbind(void) const;
		void unbindTextures(void) const;
		

	private:
		FrameBuffer m_FrameBuffer;
		Texture* m_ColorTexture;
		Texture* m_DepthTexture;
		RenderBuffer* m_RenderBuffer;
	}; // class RenderTarget
}/*namespace graphics*/ } // namespace gg

#endif
