#ifndef		GG_MESH_H
#define		GG_MESH_H
#pragma once

#include <vector>
#include "renderer/Vertex.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"
namespace gg
{
	class Mesh
	{
	public:
		Mesh(void);
		~Mesh(void);
		void setVertices(std::vector<Vertex> vertices, std::vector<uint> indices);

		void draw(void) const;

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		VertexBufferLayout layout;
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;

	}; // class Mesh
} // namespace gg

#endif
