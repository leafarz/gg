#ifndef		GG_MESHRENDERER_H
#define		GG_MESHRENDERER_H
#pragma once

#include "component/Component.h"

namespace gg { namespace graphics { class Renderer; class Mesh; class Material; } }

namespace gg
{
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
		inline graphics::Mesh* getMesh() const { return m_Mesh; }

		void setMaterial(graphics::Material* material);
		inline graphics::Material* getMaterial() const { return m_Material; }

	private:
		void draw(void);

	private:
		graphics::Mesh* m_Mesh;
		graphics::Material* m_Material;
	}; // class MeshRenderer
} // namespace gg

#endif
