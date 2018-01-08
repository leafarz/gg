#ifndef		GG_INDEXBUFFER_H
#define		GG_INDEXBUFFER_H
#pragma once

#include "core/Types.h"
namespace gg
{
	class IndexBuffer
	{
	public:
		IndexBuffer(void);
		IndexBuffer(const uint *data, uint count);
		~IndexBuffer(void);

		inline uint getCount(void) const { return m_Count; }

		void initData(const uint *data, uint count);
		void bind(void) const;
		void unbind(void) const;
	private:
		uint m_ID;
		uint m_Count;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
} // namespace gg

#endif
