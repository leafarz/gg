#include "renderer/Renderer.h"

namespace gg
{
	Renderer::Renderer(void)
	{
	}

	Renderer::~Renderer(void)
	{
	}

	void Renderer::onRender(void) const
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// process render commands
	}

} // namespace gg
