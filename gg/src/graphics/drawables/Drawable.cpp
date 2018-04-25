#include "graphics/drawables/Drawable.h"

#include "graphics/Shader.h"

namespace gg { namespace graphics {
	Drawable::Drawable(void)
	{ }
	Drawable::~Drawable(void)
	{ }

	void Drawable::begin(const math::Mat4f& pvMatrix)
	{
		m_Shader->bind();
		m_Shader->setUniform("mvp", pvMatrix, true);
		m_VA.bind();
		m_IB.bind();
	}
}/*graphics*/ } // namespace gg
