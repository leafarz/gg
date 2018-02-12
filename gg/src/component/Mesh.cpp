#include "component/Mesh.h"

namespace gg
{
	Mesh::Mesh(void)
	{
	}

	Mesh::~Mesh(void)
	{ }

	void Mesh::setVertices(const std::vector<Vertex>& vertices, const std::vector<uint>& indices)
	{
		m_Vertices = vertices;
		m_Indices = indices;

		vb.setData(&m_Vertices.front(), m_Vertices.size() * sizeof(Vertex));
		ib.setData(&m_Indices.front(), m_Indices.size());

		VertexBufferLayout _layout = VertexBufferLayout();
		_layout.Push<float>(3);	// position
		_layout.Push<float>(2);	// uv
		_layout.Push<float>(3);	// normal
		_layout.Push<float>(4);	// color

		va.init();
		va.addBuffer(vb, _layout);
	}

	void Mesh::draw(void) const
	{
		va.bind();
		ib.bind();
		glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}
} // namespace gg
