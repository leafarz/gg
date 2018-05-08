#ifndef		GG_RENDERBUFFER_H
#define		GG_RENDERBUFFER_H
#pragma once

#include "GL/glew.h"

namespace gg { namespace graphics {
	class RenderBuffer
	{
	private:
		friend class FrameBuffer;
		friend class Renderer;

	public:
		/* Empty constructor.
		 * init() must be called to be able to generate RenderBuffer data.
		 */
		RenderBuffer(void);
		~RenderBuffer(void);

		void init(float width, float height);

	private:
		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class RenderBuffer
}/*namespace graphics*/ } // namespace gg

#endif
