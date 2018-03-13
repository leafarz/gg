#ifndef		GG_MESHRENDERER_H
#define		GG_MESHRENDERER_H
#pragma once

#include "component/Component.h"

namespace gg
{
	namespace graphics { class Renderer; class Mesh; class Material; }
	class MeshRenderer : public Component
	{
	private:
		friend class graphics::Renderer;

	public:
		MeshRenderer(void);
		MeshRenderer(graphics::Mesh* mesh, graphics::Material* material);
		~MeshRenderer(void);

		static ComponentType getStaticType(void) { return ComponentType::MeshRenderer; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void setMesh(graphics::Mesh* mesh);
		graphics::Mesh* getMesh() const;

		void setMaterial(graphics::Material* material);
		graphics::Material* getMaterial() const;

	private:
		void draw(void);

	private:
		graphics::Mesh* m_Mesh;
		graphics::Material* m_Material;
	}; // class MeshRenderer
} // namespace gg

#endif
