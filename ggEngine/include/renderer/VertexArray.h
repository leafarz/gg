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
		VertexArray(void);
		~VertexArray(void);

		void init(void);
		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void bind(void) const;
		void unbind(void) const;

	private:
		GLuint m_ID;
	}; // class VertexArray
} // namespace gg

#endif
