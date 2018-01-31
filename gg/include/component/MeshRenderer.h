#ifndef		GG_MESHRENDERER_H
#define		GG_MESHRENDERER_H
#pragma once

namespace gg
{
	class Mesh;
	class Material;
	class MeshRenderer
	{
	public:
		MeshRenderer(void);
		MeshRenderer(Mesh* mesh, Material* material);
		~MeshRenderer(void);

	private:
		Mesh* m_Mesh;
		Material* m_Material;
	}; // class MeshRenderer
} // namespace gg

#endif
