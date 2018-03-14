#ifndef		GG_SubMesh_H
#define		GG_SubMesh_H
#pragma once

#include <vector>

#include "graphics/IndexBuffer.h"
#include "graphics/Vertex.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"

namespace gg { namespace graphics {
	class SubMesh
	{
	public:
		SubMesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, bool calculateNormals = false);
		SubMesh(uint vao, uint vbo, uint ibo, GLuint indicesCount);
		~SubMesh(void);

		void draw(void) const;

	private:
		void calculateNormals(std::vector<Vertex>& vertices, std::vector<uint>& indices);

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;

		VertexArray m_VA;
		VertexBuffer m_VB;
		IndexBuffer m_IB;
	}; // class SubMesh
}/*namespace graphics*/ } // namespace gg

#endif
