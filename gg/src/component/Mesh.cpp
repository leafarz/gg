#include "component/Mesh.h"
#include "platform/opengl/GLCommon.h"
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

		m_VB.setData(&m_Vertices.front(), m_Vertices.size() * sizeof(Vertex));
		m_IB.setData(&m_Indices.front(), m_Indices.size());

		VertexBufferLayout _layout = VertexBufferLayout();
		_layout.Push<float>(3);	// position
		_layout.Push<float>(2);	// uv
		_layout.Push<float>(3);	// normal
		_layout.Push<float>(4);	// color

		m_VA.init();
		m_VA.addBuffer(m_VB, _layout);
	}

	void Mesh::draw(void) const
	{
		m_VA.bind();
		m_IB.bind();
		GL(glDrawElements(GL_TRIANGLES, m_IB.getCount(), GL_UNSIGNED_INT, nullptr));
	}
} // namespace gg
