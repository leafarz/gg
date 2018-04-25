#include "graphics/Mesh.h"

#include "graphics/SubMesh.h"
#include "util/Iterators.h"

#include "security/cryptography/crc32.h"

namespace gg { namespace graphics {
	std::unordered_map<uint, std::vector<SubMesh*>> Mesh::s_SubMeshHash;

	Mesh::Mesh(void)
	{ }

	Mesh::Mesh(const std::string& filePath, bool calculateNormals)
		: m_FilePath(filePath)
	{
		_SYS("Processing file: \"" << m_FilePath << "\"");

		// check first if file is already cached
		m_SubMeshHash = Crc32::getHash(m_FilePath.c_str(), m_FilePath.size());
		bool _isCached = s_SubMeshHash.find(m_SubMeshHash) != s_SubMeshHash.end();

		if (_isCached)
		{
			_SYS("Fetching cached mesh data: \"" << m_FilePath << "\"");
			const std::vector<SubMesh*>& _subMeshes= s_SubMeshHash[m_SubMeshHash];
			m_SubMeshes = _subMeshes;
			return;
		}

		Assimp::Importer importer;
		const aiScene* _scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
		if (!_scene || _scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_scene->mRootNode)
		{
			ERROR("Error loading model from [" << filePath << ']');
		}

		processNode(_scene->mRootNode, _scene, calculateNormals);

		s_SubMeshHash[m_SubMeshHash] = m_SubMeshes;
	}

	Mesh::~Mesh(void)
	{ }

	void Mesh::setVertices(std::vector<Vertex>& vertices, std::vector<uint>& indices, bool calculateNormals)
	{
		m_SubMeshes.push_back(new SubMesh(vertices, indices, calculateNormals));
	}

	void Mesh::draw(void) const
	{
		VFOR(it, m_SubMeshes)
		{
			(*it)->draw();
		}
	}

	void Mesh::processNode(aiNode* node, const aiScene* scene, bool calculateNormals)
	{
		FORU(i, 0, node->mNumMeshes)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, calculateNormals);
		}

		FORU(i, 0, node->mNumChildren)
		{
			processNode(node->mChildren[i], scene, calculateNormals);
		}
	}
	void Mesh::processMesh(aiMesh* mesh, bool calculateNormals)
	{
		std::vector<Vertex> _verts;
		std::vector<uint> _indices;

		uint _indicesLength = 0;
		FORU(i, 0, mesh->mNumFaces)
		{
			_indicesLength += mesh->mFaces[i].mNumIndices;
		}

		_verts.reserve(mesh->mNumVertices);
		_indices.reserve(_indicesLength);
		
		FORU(i, 0, mesh->mNumVertices)
		{
			_verts.push_back(
				Vertex(
					math::Vec3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
					(mesh->mTextureCoords[0] == nullptr)? math::Vec2f() : math::Vec2f(mesh->mTextureCoords[0]->x, mesh->mTextureCoords[0]->y),
					(mesh->mNormals == nullptr)			? math::Vec3f() : math::Vec3f(mesh->mNormals->x, mesh->mNormals->y, mesh->mNormals->z)
				)
			);
		}

		FORU(i, 0, mesh->mNumFaces)
		{
			aiFace _face = mesh->mFaces[i];

			FORU(j, 0, _face.mNumIndices)
			{
				_indices.push_back(_face.mIndices[j]);
			}
		}

		m_SubMeshes.push_back(new SubMesh(_verts, _indices, calculateNormals));
	}
}/*namespace graphics*/ } // namespace gg
