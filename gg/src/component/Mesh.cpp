#include "component/Mesh.h"

#include "util/Iterators.h"
#include "platform/opengl/GLCommon.h"

#include "security/cryptography/crc32.h"

namespace gg
{
	std::unordered_map<uint, Mesh::MeshData> Mesh::s_MeshDataHash;

	Mesh::Mesh(void)
	{ }

	Mesh::Mesh(const std::string& filePath, bool calculateNormals)
		: m_FilePath(filePath)
	{
		_SYS("Processing file: \"" << m_FilePath << "\"");

		// check first if file is already cached
		m_MeshDataHash = Crc32::getHash(m_FilePath.c_str(), m_FilePath.size());
		bool _isCached = s_MeshDataHash.find(m_MeshDataHash) != s_MeshDataHash.end();

		if (_isCached)
		{
			_SYS("Fetching cached mesh data: \"" << m_FilePath << "\"");
			const MeshData& _meshData = s_MeshDataHash[m_MeshDataHash];

			m_VB.setData(_meshData.vbo);
			m_IB.setData(_meshData.ibo, _meshData.indicesCount);
			m_VA.init(_meshData.vao);
			return;
		}

		Assimp::Importer _importer;
		const aiScene* _scene = _importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
		{
			ERROR("Error loading model from [" << filePath << ']');
		}

		std::vector<graphics::Vertex> _vertices;
		std::vector<uint> _indices;
		uint _vertexLength = 0;
		uint _indexLength = 0;

		getLengths(_scene->mRootNode, _scene, _vertexLength, _indexLength);
		_vertices.reserve(_vertexLength);
		_indices.reserve(_indexLength);

		processNode(_scene->mRootNode, _scene, _vertices, _indices);

		setVertices(_vertices, _indices, calculateNormals);
		s_MeshDataHash[m_MeshDataHash] = MeshData(m_VA.getID(), m_VB.getID(), m_IB.getID(), m_IB.getCount());
	}

	Mesh::~Mesh(void)
	{ }

	void Mesh::setVertices(std::vector<graphics::Vertex>& vertices, std::vector<uint>& indices, bool calculateNormals)
	{
		if (calculateNormals)
		{
			Mesh::calculateNormals(vertices, indices);
		}

		m_Vertices = vertices;
		m_Indices = indices;

		m_VB.setData(&m_Vertices.front(), m_Vertices.size() * sizeof(graphics::Vertex));
		m_IB.setData(&m_Indices.front(), m_Indices.size());

		graphics::VertexBufferLayout _layout = graphics::VertexBufferLayout();
		_layout.push<float>(3);	// position
		_layout.push<float>(2);	// uv
		_layout.push<float>(3);	// normal
		_layout.push<float>(4);	// color

		m_VA.init();
		m_VA.addBuffer(m_VB, _layout);
	}

	void Mesh::draw(void) const
	{
		m_VA.bind();
		m_IB.bind();
		GL(glDrawElements(GL_TRIANGLES, m_IB.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void Mesh::calculateNormals(std::vector<graphics::Vertex>& vertices, std::vector<uint>& indices)
	{
		for (uint i = 0; i < indices.size(); i += 3)
		{
			int _i0 = indices[i];
			int _i1 = indices[i + 1];
			int _i2 = indices[i + 2];

			Math::Vec3f _v1 = vertices[_i1].position - vertices[_i0].position;
			Math::Vec3f _v2 = vertices[_i2].position - vertices[_i0].position;

			Math::Vec3f _normal = _v1.cross(_v2).normal();

			vertices[_i0].normal = _normal;
			vertices[_i1].normal = _normal;
			vertices[_i2].normal = _normal;
		}

		FORU(i, 0, vertices.size())
		{
			vertices[i].normal.normalize();
		}
	}

	void Mesh::getLengths(aiNode* node, const aiScene* scene, uint& vertsLength, uint& indicesLength)
	{
		FORU(i, 0, node->mNumMeshes)
		{
			aiMesh* _mesh = scene->mMeshes[node->mMeshes[i]];
			vertsLength += _mesh->mNumVertices;

			FORU(i, 0, _mesh->mNumFaces)
			{
				indicesLength += _mesh->mFaces[i].mNumIndices;
			}
		}

		FORU(i, 0, node->mNumChildren)
		{
			getLengths(node->mChildren[i], scene, vertsLength, indicesLength);
		}
	}

	void Mesh::processNode(aiNode* node, const aiScene* scene, std::vector<graphics::Vertex>& verts, std::vector<GLuint>& indices)
	{
		FORU(i, 0, node->mNumMeshes)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, verts, indices);
		}

		FORU(i, 0, node->mNumChildren)
		{
			processNode(node->mChildren[i], scene, verts, indices);
		}
	}
	void Mesh::processMesh(aiMesh* mesh, std::vector<graphics::Vertex>& verts, std::vector<GLuint>& indices)
	{
		FORU(i, 0, mesh->mNumVertices)
		{
			verts.push_back(
				graphics::Vertex(
					Math::Vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
					(mesh->mTextureCoords[0] == nullptr)? Math::Vec2f() : Math::Vec2f(mesh->mTextureCoords[0]->x, mesh->mTextureCoords[0]->y),
					(mesh->mNormals == nullptr)			? Math::Vec3f() : Math::Vec3f(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z)
				)
			);
		}

		FORU(i, 0, mesh->mNumFaces)
		{
			aiFace _face = mesh->mFaces[i];

			FORU(j, 0, _face.mNumIndices)
			{
				indices.push_back(_face.mIndices[j]);
			}
		}
	}
} // namespace gg
