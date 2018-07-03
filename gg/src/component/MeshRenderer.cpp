#include "component/MeshRenderer.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"

namespace gg
{
	MeshRenderer::MeshRenderer(void)
	{ }

	MeshRenderer::MeshRenderer(graphics::Mesh* mesh, graphics::Material* material)
		: m_Mesh(mesh), m_Material(material)
	{ }

	MeshRenderer::~MeshRenderer(void)
	{
		// TODO: add destroy on mesh if no one is referencing it
		// TODO: add destroy on material if no one is referencing it
	}

	void MeshRenderer::setMesh(graphics::Mesh* mesh) { m_Mesh = mesh; }

	void MeshRenderer::setMaterial(graphics::Material* material) { m_Material = material; }

	void MeshRenderer::draw(void)
	{
		m_Material->bind();
		m_Material->updateUniforms();
		m_Mesh->draw();
	}
} // namespace gg
