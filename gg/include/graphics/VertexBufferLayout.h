#ifndef		GG_VERTEXBUFFERLAYOUT_H
#define		GG_VERTEXBUFFERLAYOUT_H
#pragma once

#include <vector>
#include "debug/Log.h"
#include "core/Types.h"
#include "platform/opengl/GLCommon.h"

namespace gg { namespace graphics {
	class VertexBufferLayout
	{
	private:
		struct VertexBufferElement
		{
			uint count;
			uint type;
			unsigned char normalized;
			VertexBufferElement(uint type, uint count, unsigned char normalized)
				: type(type), count(count), normalized(normalized)
			{ }

			/* Returns the size in bytes of the type assigned to this struct */
			inline uint getSize() const
			{
				return getSizeOfType(type);
			}

			/* Returns the size in bytes of the gl type of the param passed. */
			static uint getSizeOfType(uint type)
			{
				switch (type)
				{
				case GL_FLOAT:			return 4;
				case GL_UNSIGNED_INT:	return 4;
				case GL_UNSIGNED_BYTE:	return 1;
				}

				ERROR("Unhandled type:" << type);
				ASSERT(false);
				return 0;
			}
		};

	public:
		VertexBufferLayout(void);
		~VertexBufferLayout(void);

		template<typename T> void push(uint count) { static_assert(false); }
		template<> void push<float>(uint count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
		}
		template<> void push<uint>(uint count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
		}
		template<> void push<unsigned char>(uint count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
		}


		inline const std::vector<VertexBufferElement>& getElements() const { return m_Elements; }
		inline uint getStride() const { return m_Stride; }
	private:
		std::vector<VertexBufferElement> m_Elements;
		uint m_Stride;
	}; // class VertexBufferLayout
}/*namespace graphics*/ } // namespace gg

#endif
