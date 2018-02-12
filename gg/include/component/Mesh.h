#ifndef		GG_MESH_H
#define		GG_MESH_H
#pragma once

#include <vector>
#include "renderer/Vertex.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"

#include "component/Component.h"
namespace gg
{
	class Mesh : public Component
	{
	private:
		friend class MeshRenderer;
	public:
		Mesh(void);
		~Mesh(void);

		static ComponentType getStaticType(void) { return ComponentType::Mesh; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setVertices(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

	private:
		void draw(void) const;

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		VertexArray m_VA;
		VertexBuffer m_VB;
		IndexBuffer m_IB;

	}; // class Mesh
} // namespace gg

#endif
