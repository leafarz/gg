#include "component/Mesh.h"
#include "platform/opengl/GLCommon.h"

#include "security/cryptography/crc32.h"

namespace gg
{
	std::unordered_map<uint, Mesh::MeshData> Mesh::s_MeshDataHash;

	Mesh::Mesh(void)
	{ }

	Mesh::Mesh(const std::string& filePath)
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

		std::vector<Vertex> _vertices;
		std::vector<uint> _indices;

		Assimp::Importer _importer;
		const aiScene* _scene = _importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!_scene)
		{
			ERROR("Error loading model from [" << filePath << ']');
		}

		processModel(_scene->mRootNode, _scene, _vertices, _indices);

		setVertices(_vertices, _indices);
		s_MeshDataHash[m_MeshDataHash] = MeshData(m_VA.getID(), m_VB.getID(), m_IB.getID(), m_IB.getCount());
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
	void Mesh::processModel(aiNode* node, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices)
	{
		// Process each mesh located at the current node
		FORU(i, 0, node->mNumMeshes)
		{
			// The scene contains all the data
			aiMesh* _mesh = scene->mMeshes[node->mMeshes[i]];

			processMesh(_mesh, scene, verts, indices);
		}

		FORU(i, 0, node->mNumChildren)
		{
			processNode(node->mChildren[i], scene, verts, indices);
		}
	}
	void Mesh::processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices)
	{
		FORU(i, 0, mesh->mNumVertices)
		{
			verts.push_back(
				Vertex(
					Math::Vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
					Math::Vec2f(mesh->mTextureCoords[0]->x, mesh->mTextureCoords[0]->y),
					Math::Vec3f(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z)
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
	void Mesh::processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices)
	{
		FORU(i, 0, node->mNumMeshes)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene, verts, indices);
		}

		FORU(i, 0, node->mNumChildren)
		{
			processNode(node->mChildren[i], scene, verts, indices);
		}
	}
} // namespace gg
