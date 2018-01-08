#ifndef		GG_VERTEXBUFFER_H
#define		GG_VERTEXBUFFER_H
#pragma once

#include "core/Types.h"
namespace gg
{
	class VertexBuffer
	{
	public:
		VertexBuffer(void);
		VertexBuffer(const void *data, uint size);
		~VertexBuffer(void);

		void initData(const void *data, uint size);
		void bind(void) const;
		void unbind(void) const;
	private:
		uint m_ID;
		bool m_IsInitialized = false;
	}; // class VertexBuffer
} // namespace gg

#endif
