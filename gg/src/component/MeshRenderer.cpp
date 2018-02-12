#include "component/MeshRenderer.h"

#include "component/Mesh.h"
#include "renderer/Material.h"

namespace gg
{
	MeshRenderer::MeshRenderer(void)
	{ }

	MeshRenderer::MeshRenderer(Mesh * mesh, Material * material)
		: m_Mesh(mesh), m_Material(material)
	{ }

	MeshRenderer::~MeshRenderer(void)
	{
		// TODO: add destroy on mesh if no one is referencing it
		// TODO: add destroy on material if no one is referencing it
	}

	void MeshRenderer::setMesh(Mesh* mesh) { m_Mesh = mesh; }
	Mesh* MeshRenderer::getMesh() const { return m_Mesh; }

	void MeshRenderer::setMaterial(Material* material) { m_Material = material; }
	Material* MeshRenderer::getMaterial() const { return m_Material; }

	void MeshRenderer::draw(void)
	{
		m_Material->updateUniforms();
		m_Material->bind();
		m_Mesh->draw();
	}
} // namespace gg
