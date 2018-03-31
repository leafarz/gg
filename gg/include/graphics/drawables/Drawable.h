#ifndef		GG_Drawable_H
#define		GG_Drawable_H
#pragma once

#include "graphics/IndexBuffer.h"
#include "graphics/Vertex.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBuffer.h"
#include "graphics/VertexBufferLayout.h"

#include "math/Mat4f.h"

namespace gg { namespace graphics {
	class Shader;
	class Drawable
	{
	public:
		Drawable(void);
		~Drawable(void);

		virtual void begin(const Math::Mat4f& pvMatrix);

	protected:
		graphics::Shader* m_Shader;

		graphics::VertexArray m_VA;
		graphics::VertexBuffer m_VB;
		graphics::IndexBuffer m_IB;

		std::vector<graphics::Vertex> m_Vertices;
	}; // class Drawable
}/*graphics*/ } // namespace gg

#endif
