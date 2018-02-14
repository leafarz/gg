#ifndef		GG_MESH_H
#define		GG_MESH_H
#pragma once

#include <vector>
#include <unordered_map>
#include "graphics/Vertex.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/IndexBuffer.h"

#include "component/Component.h"

/* assimp include files. These three are usually needed. */
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace gg
{
	class Mesh : public Component
	{
	private:
		friend class MeshRenderer;

	private:
		struct MeshData
		{
		public:
			GLuint vao;
			GLuint vbo;
			GLuint ibo;
			uint indicesCount;

			MeshData(void)
			{ }
			MeshData(GLuint vao, GLuint vbo, GLuint ibo, uint indicesCount)
				: vao(vao), vbo(vbo), ibo(ibo), indicesCount(indicesCount)
			{ }
		};
	public:
		Mesh(void);
		Mesh(const std::string& filePath);
		~Mesh(void);

		static ComponentType getStaticType(void) { return ComponentType::Mesh; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setVertices(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);

	private:
		void draw(void) const;

		// TODO: add calculate normals

		void processModel(aiNode* node, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices);
		void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices);
		void processNode(aiNode* node, const aiScene* scene, std::vector<Vertex>& verts, std::vector<GLuint>& indices);

	private:
		/* Key value pairs of hash to ids created throughout the app. */
		static std::unordered_map<uint, MeshData> s_MeshDataHash;

		uint m_MeshDataHash;
		std::string m_FilePath;

		// TODO: remove or update use for verts and indices

		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		VertexArray m_VA;
		VertexBuffer m_VB;
		IndexBuffer m_IB;

	}; // class Mesh
} // namespace gg

#endif
