#ifndef		GG_FRAMEBUFFER_H
#define		GG_FRAMEBUFFER_H
#pragma once

#include "GL/glew.h"

#include <vector>

#include "core/Types.h"

namespace gg { namespace graphics {
	class RenderBuffer;
	class Texture;

	class FrameBuffer
	{
	private:
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
		void init(uint width, uint height);

		void addColorTexture(uint width, uint height);
		void addDepthTexture(uint width, uint height);
		void addRenderBuffer(uint width, uint height);

	private:
		void bind(void) const;
		void bindColorTexture(uint samplerSlot) const;
		void bindDepthTexture(uint samplerSlot) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;

		Texture* m_ColorTexture;
		Texture* m_DepthTexture;
		RenderBuffer* m_RenderBuffer;
	}; // class FrameBuffer
}/*namespace graphics*/ } // namespace gg

#endif
