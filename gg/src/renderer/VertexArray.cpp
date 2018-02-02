#include "renderer/VertexArray.h"

#include "platform/opengl/GLCommon.h"
#include "core/gg.h"

namespace gg
{
	VertexArray::VertexArray(void)
	{
	}

	VertexArray::~VertexArray(void)
	{
		GL(glDeleteVertexArrays(1, &m_ID));
	}

	void VertexArray::init(void)
	{
		if (m_IsInitialized)
		{
			GL(glDeleteVertexArrays(1, &m_ID));
		}
		GL(glGenVertexArrays(1, &m_ID));
		m_IsInitialized = true;
	}

	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		bind();
		vb.bind();
		const auto& _elements = layout.GetElements();
		uint _offset = 0;
		FORU(i, 0, _elements.size())
		{
			const auto& _element = _elements[i];
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, _element.count, _element.type, _element.normalized, layout.GetStride(), (const void*)_offset));
			_offset += _element.count * _element.getSize();
		}
	}
	void VertexArray::bind(void) const
	{
		GL(glBindVertexArray(m_ID));
	}
	void VertexArray::unbind(void) const
	{
		GL(glBindVertexArray(0));
	}
} // namespace gg
