#include "graphics/SubMesh.h"

#include "util/Iterators.h"

namespace gg { namespace graphics {
	SubMesh::SubMesh(std::vector<Vertex>& vertices, std::vector<uint>& indices, bool calculateNormals)
	{
		if (calculateNormals)
		{
			SubMesh::calculateNormals(vertices, indices);
		}

		m_Vertices = vertices;
		m_Indices = indices;

		m_VB.setData(&m_Vertices.front(), m_Vertices.size() * sizeof(Vertex), false);
		m_IB.setData(&m_Indices.front(), m_Indices.size());

		VertexBufferLayout _layout = VertexBufferLayout();
		_layout.push<float>(3);	// position
		_layout.push<float>(2);	// uv
		_layout.push<float>(3);	// normal
		_layout.push<float>(4);	// color

		m_VA.init();
		m_VA.addBuffer(m_VB, _layout);
	}

	SubMesh::SubMesh(uint vao, uint vbo, uint ibo, GLuint indicesCount)
	{
		m_VB.setData(vbo);
		m_IB.setData(ibo, indicesCount);
		m_VA.init(vao);
	}

	SubMesh::~SubMesh(void)
	{
	}

	void SubMesh::draw(void) const
	{
		m_VA.bind();
		m_IB.bind();
		GL(glDrawElements(GL_TRIANGLES, m_IB.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void SubMesh::calculateNormals(std::vector<Vertex>& vertices, std::vector<uint>& indices)
	{
		for (uint i = 0; i < indices.size(); i += 3)
		{
			int _i0 = indices[i];
			int _i1 = indices[i + 1];
			int _i2 = indices[i + 2];

			math::Vec3f _v1 = vertices[_i1].position - vertices[_i0].position;
			math::Vec3f _v2 = vertices[_i2].position - vertices[_i0].position;

			math::Vec3f _normal = _v1.cross(_v2).normal();

			vertices[_i0].normal = _normal;
			vertices[_i1].normal = _normal;
			vertices[_i2].normal = _normal;
		}

		FORU(i, 0, vertices.size())
		{
			vertices[i].normal.normalize();
		}
	}
}/*namespace graphics*/ } // namespace gg
