#include "renderer/Renderer.h"

#include "entity/GameObject.h"
#include "renderer/Material.h"

#include "core/gg.h"
namespace gg
{
	Renderer::Renderer(void)
	{
		glFrontFace(GL_CW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	Renderer::~Renderer(void)
	{
	}

	void Renderer::draw(GameObject* gameObject, const Math::Mat4f& pvMatrix)
	{
		MeshRenderer* _mr = gameObject->getComponent<MeshRenderer>();
		if (!_mr) { return; }

		// add system uniforms
		Transform* _t = gameObject->getTransform();
		_mr->getMaterial()->setUniform("mvp", pvMatrix * _t->getTransformationMatrix());
		_mr->draw();

		// TODO: get mesh, material and transform
		// va.bind();
		// ib.bind();
		// glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::begin(void) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_BLEND);
		// process render commands
	}

} // namespace gg
