#ifndef		GG_VERTEXBUFFER_H
#define		GG_VERTEXBUFFER_H
#pragma once

#include "GL/glew.h"
#include "core/Types.h"
namespace gg
{
	class VertexBuffer
	{
	public:
		/* Empty constructor.
		 * initData() must be called to initialize data.
		 */
		VertexBuffer(void);

		/* Initializes the buffer id and buffer data.
		 * Binds the current buffer.
		 * [data]	- the data of the buffer
		 * [size]	- the size of data in bytes
		 */
		VertexBuffer(const void *data, uint size);
		~VertexBuffer(void);

		/* Sets the buffer id and buffer data.
		 * Binds the current buffer.
		 * Will do nothing if called repeatedly.
		 * [data]	- the data of the buffer
		 * [size]	- the size of data in bytes
		 */
		void setData(const void *data, uint size);

		/* Binds the current vertex buffer. */
		void bind(void) const;

		/* Uninds the current vertex buffer. */
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
} // namespace gg

#endif
