#ifndef		GG_MESHRENDERER_H
#define		GG_MESHRENDERER_H
#pragma once

#include "component/Component.h"

namespace gg
{
	class Mesh;
	class Material;
	class MeshRenderer : public Component
	{
	private:
		friend class Renderer;

	public:
		MeshRenderer(void);
		MeshRenderer(Mesh* mesh, Material* material);
		~MeshRenderer(void);

		static ComponentType getStaticType(void) { return ComponentType::MeshRenderer; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setMesh(Mesh* mesh);
		Mesh* getMesh() const;

		void setMaterial(Material* material);
		Material* getMaterial() const;

	private:
		void draw(void);

	private:
		Mesh* m_Mesh;
		Material* m_Material;
	}; // class MeshRenderer
} // namespace gg

#endif
