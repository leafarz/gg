#include "component/MeshRenderer.h"

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
} // namespace gg
