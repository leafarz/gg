#ifndef		GG_RENDERTARGET_H
#define		GG_RENDERTARGET_H
#pragma once

#include "core/Types.h"

#include "graphics/FrameBuffer.h"

namespace gg { namespace graphics { class Texture; } }

namespace gg { namespace graphics {
	class RenderTarget
	{
	private:
		friend class Renderer;

	public:
		RenderTarget(void);
		~RenderTarget(void);

		void init(uint width, uint height);

	private:
		void bind(void) const;
		void bindTextures(void) const;
		void unbind(void) const;
		

	private:
		FrameBuffer m_FrameBuffer;
	}; // class RenderTarget
}/*namespace graphics*/ } // namespace gg

#endif
