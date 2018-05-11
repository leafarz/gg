#ifndef		GG_RENDERTARGET_H
#define		GG_RENDERTARGET_H
#pragma once

#include "graphics/FrameBuffer.h"

namespace gg { namespace graphics { class Texture; } }

namespace gg { namespace graphics {
	class RenderTarget
	{
	public:
		RenderTarget(void);
		~RenderTarget(void);

	private:
		FrameBuffer m_FrameBuffer;
		Texture* m_Texture;
	}; // class RenderTarget
}/*namespace graphics*/ } // namespace gg

#endif
