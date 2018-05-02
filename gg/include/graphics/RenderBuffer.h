#ifndef		GG_RENDERBUFFER_H
#define		GG_RENDERBUFFER_H
#pragma once

#include "GL/glew.h"

namespace gg { namespace graphics {
	class RenderBuffer
	{
	public:
		RenderBuffer(void);
		~RenderBuffer(void);

		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class RenderBuffer
}/*namespace graphics*/ } // namespace gg

#endif
