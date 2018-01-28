#ifndef		GG_RENDERER_H
#define		GG_RENDERER_H
#pragma once

#include "platform/opengl/GLCommon.h"

namespace gg
{
	class GameObject;
	class Renderer
	{
	public:
		Renderer(void);
		~Renderer(void);

		void begin(void) const;
		void draw(GameObject* gameObject);
	}; // class Renderer
} // namespace gg

#endif
