#ifndef		GG_FRAMEBUFFER_H
#define		GG_FRAMEBUFFER_H
#pragma once

#include "GL/glew.h"

namespace gg { namespace graphics {
	class FrameBuffer
	{
	public:
		/* Empty constructor.
		 * init() must be called to be able to generate FrameBuffer data.
		 */
		FrameBuffer(void);
		~FrameBuffer(void);

		/* Generates FrameBuffer id. */
		void init(void);

		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class FrameBuffer
}/*namespace graphics*/ } // namespace gg

#endif
