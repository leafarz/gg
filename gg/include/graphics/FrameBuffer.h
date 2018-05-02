#ifndef		GG_FRAMEBUFFER_H
#define		GG_FRAMEBUFFER_H
#pragma once

#include "GL/glew.h"

namespace gg { namespace graphics {
	class FrameBuffer
	{
	public:
		FrameBuffer(void);
		~FrameBuffer(void);

		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class FrameBuffer
}/*namespace graphics*/ } // namespace gg

#endif
