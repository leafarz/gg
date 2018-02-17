#ifndef		GG_RENDERER_H
#define		GG_RENDERER_H
#pragma once

#include "platform/opengl/GLCommon.h"

#include "math/Mat4f.h"

namespace gg
{
	class GameObject;
	class Renderer
	{
	public:
		Renderer(void);
		~Renderer(void);

		void begin(void) const;
		void draw(GameObject* gameObject, const Math::Mat4f& viewMatrix, const Math::Mat4f& projectionMatrix, const Math::Mat4f& pvMatrix);
	}; // class Renderer
} // namespace gg

#endif
