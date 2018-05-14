#ifndef		GG_FRAMEBUFFER_H
#define		GG_FRAMEBUFFER_H
#pragma once

#include "GL/glew.h"

#include <vector>

#include "core/Types.h"

namespace gg { namespace graphics { class RenderBuffer; class Texture; } }

namespace gg { namespace graphics {
	class FrameBuffer
	{
	private:
		friend class RenderTarget;
		friend class Renderer;

	public:
		/* Empty constructor.
		 * init() must be called to be able to generate FrameBuffer data.
		 */
		FrameBuffer(void);
		~FrameBuffer(void);

		/* Generates FrameBuffer id.
		 * Adds the color and depth textures.
		 */
		void init(uint width, uint height, Texture* colorTexture, Texture* depthTexture);

	private:
		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class FrameBuffer
}/*namespace graphics*/ } // namespace gg

#endif
