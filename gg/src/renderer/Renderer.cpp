#include "renderer/Renderer.h"

#include "entity/GameObject.h"
#include "renderer/Material.h"

namespace gg
{
	Renderer::Renderer(void)
	{
	}

	Renderer::~Renderer(void)
	{
	}

	void Renderer::draw(GameObject* gameObject, const Math::Mat4f& pvMatrix)
	{
		MeshRenderer* _mr = gameObject->getComponent<MeshRenderer>();

		// add system uniforms

		_mr->draw();

		// TODO: get mesh, material and transform
		// va.bind();
		// ib.bind();
		// glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::begin(void) const
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// process render commands
	}

} // namespace gg
