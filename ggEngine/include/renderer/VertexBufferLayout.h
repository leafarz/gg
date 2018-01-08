#ifndef		GG_VERTEXBUFFERLAYOUT_H
#define		GG_VERTEXBUFFERLAYOUT_H
#pragma once

#include <vector>
#include "core/Types.h"
#include "platform/opengl/GLCommon.h"

namespace gg
{
	class VertexBufferLayout
	{
	private:
		enum class DataType : ubyte
		{
			FLOAT = 0,
			UNSIGNED_INT = 1,
			UNSIGNED_CHAR = 2
		};

		struct VertexBufferElement
		{
			DataType dataType;
			uint count;
			bool normalized;
			VertexBufferElement(DataType dataType, uint count, bool normalized)
				: dataType(dataType), count(count), normalized(normalized)
			{ }
		};

	public:
		VertexBufferLayout(void);
		~VertexBufferLayout(void);

		template<typename T> void Push(uint count) { static_assert(false); }
		template<> void Push<float>(uint count)
		{
			m_Elements.push_back({ DataType::FLOAT, count, false });
			m_Stride += sizeof(GL_FLOAT);
		}
		template<> void Push<uint>(uint count)
		{
			m_Elements.push_back({ DataType::UNSIGNED_INT, count, false });
			m_Stride += sizeof(GL_UNSIGNED_INT);
		}
		template<> void Push<unsigned char>(uint count)
		{
			m_Elements.push_back({ DataType::UNSIGNED_CHAR, count, true });
			m_Stride += sizeof(GL_UNSIGNED_BYTE);
		}


		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline uint GetStride() const { return m_Stride; }
	private:
		std::vector<VertexBufferElement> m_Elements;
		uint m_Stride;
	}; // class VertexBufferLayout
} // namespace gg

#endif
