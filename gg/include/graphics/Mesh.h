#ifndef		GG_MESH_H
#define		GG_MESH_H
#pragma once

#include <vector>
#include <unordered_map>

#include "core/Types.h"

#include "component/Component.h"

#include "graphics/Vertex.h"

/* assimp include files. These three are usually needed. */
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

// TODO: check what should be moved to SubMesh script
namespace gg { namespace graphics {
	class SubMesh;
	class Mesh
	{
	private:
		friend class MeshRenderer;

	public:
		Mesh(void);
		Mesh(const std::string& filePath, bool calculateNormals = false);
		~Mesh(void);

		void setVertices(std::vector<Vertex>& vertices, std::vector<uint>& indices, bool calculateNormals = false);

	private:
		void draw(void) const;

		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh);

	private:
		/* Key value pairs of hash to ids created throughout the app. */
		static std::unordered_map<uint, std::vector<SubMesh*>> s_SubMeshHash;

		uint m_SubMeshHash;
		std::string m_FilePath;

		// TODO: remove or update use for verts and indices

		std::vector<SubMesh*> m_SubMeshes;
	}; // class Mesh
}/*namespace graphics*/ } // namespace gg

#endif
