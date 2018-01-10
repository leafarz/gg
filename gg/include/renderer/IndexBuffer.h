#ifndef		GG_INDEXBUFFER_H
#define		GG_INDEXBUFFER_H
#pragma once

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

		inline uint getCount(void) const { return m_Count; }

		/* Initializes the buffer id and buffer data.
		 * Binds the current buffer.
		 * [data]	- the data of the buffer
		 * [count]	- number of elements in the data array
		 */
		void initData(const uint *data, uint count);

		/* Binds the current index buffer. */
		void bind(void) const;
		/* Unbinds the current index buffer. */
		void unbind(void) const;
	private:
		uint m_ID;
		uint m_Count;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
} // namespace gg

#endif
