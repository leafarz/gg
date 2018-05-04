#ifndef		GG_VERTEXBUFFER_H
#define		GG_VERTEXBUFFER_H
#pragma once

#include "GL/glew.h"
#include "core/Types.h"
namespace gg { namespace graphics {
	class VertexBuffer
	{
	public:
		/* Empty constructor.
		 * setData() must be called to initialize data.
		 */
		VertexBuffer(void);

		/* Initializes the buffer id and buffer data.
		 * Binds the current buffer.
		 * [data]	- the data of the buffer
		 * [size]	- the size of data in bytes
		 */
		VertexBuffer(const void *data, uint size);
		~VertexBuffer(void);

		GLuint getID(void) const { return m_ID; }

		/* Sets the buffer id and buffer data.
		 * Binds the current buffer.
		 * Will do nothing if called repeatedly.
		 * [data]			- the data of the buffer
		 * [size]			- the size of data in bytes
		 * [dynamicDraw]	- Flag if data will be changed often or not.
		 */
		void setData(const void *data, uint size, bool dynamicDraw);
		void setData(GLuint id);

		void updateData(const void *data, uint size, bool dynamicDraw);

		/* Binds the current vertex buffer. */
		void bind(void) const;

		/* Uninds the current vertex buffer. */
		void unbind(void) const;

	private:
		GLuint m_ID;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
}/*namespace graphics*/ } // namespace gg

#endif
