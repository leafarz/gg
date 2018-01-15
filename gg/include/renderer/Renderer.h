#ifndef		GG_RENDERER_H
#define		GG_RENDERER_H
#pragma once

#include "platform/opengl/GLCommon.h"

namespace gg
{
	class Renderer
	{
	public:
		Renderer(void);
		~Renderer(void);

		void onRender(void) const;
	}; // class Renderer
} // namespace gg

#endif
