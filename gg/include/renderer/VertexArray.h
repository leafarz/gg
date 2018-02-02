#ifndef		GG_VERTEXARRAY_H
#define		GG_VERTEXARRAY_H
#pragma once

#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"

namespace gg
{
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
} // namespace gg

#endif
