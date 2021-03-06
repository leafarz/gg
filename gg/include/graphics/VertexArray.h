#ifndef		GG_VERTEXARRAY_H
#define		GG_VERTEXARRAY_H
#pragma once

#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"

namespace gg { namespace graphics {
	class VertexArray
	{
	public:
		/* Empty constructor.
		 * init() must be called to be able to generate VertexArray data.
		 */
		VertexArray(void);
		~VertexArray(void);

		/* Generates VertexArray id. */
		void init(void);
		void init(GLuint id);

		inline GLuint getID(void) const { return m_ID; }

		/* Adds the vertex buffer with its layout to the vertex array.
		 * Binds the current vertex array.
		 * [vb]		- the vertex buffer to be bound to the current vertex array.
		 * [layout]	- the layout of the vertex buffer param.
		 */
		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		/* Binds the current vertex array. */
		void bind(void) const;

		/* Unbinds the current vertex array. */
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class VertexArray
}/*namespace graphics*/ } // namespace gg

#endif
