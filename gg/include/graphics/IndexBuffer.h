#ifndef		GG_INDEXBUFFER_H
#define		GG_INDEXBUFFER_H
#pragma once

#include "GL/glew.h"
#include "core/Types.h"
namespace gg
{
	class IndexBuffer
	{
	public:
		/* Empty constructor.
		 * initData() must be called to initialize data.
		 */
		IndexBuffer(void);

		/* Initializes the buffer id and buffer data.
		 * Binds the current buffer.
		 * [data]	- the data of the buffer
		 * [count]	- number of elements in the data array
		 */
		IndexBuffer(const uint *data, uint count);
		~IndexBuffer(void);

		uint getCount(void) const { return m_Count; }
		GLuint getID(void) const { return m_ID; }

		/* Sets the buffer id and buffer data.
		 * Binds the current buffer.
		 * [data]	- the data of the buffer
		 * [count]	- number of elements in the data array
		 */
		void setData(const uint *data, uint count);
		void setData(GLuint id, uint count);

		/* Binds the current index buffer. */
		void bind(void) const;
		/* Unbinds the current index buffer. */
		void unbind(void) const;

	private:
		GLuint m_ID;
		uint m_Count;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
} // namespace gg

#endif
