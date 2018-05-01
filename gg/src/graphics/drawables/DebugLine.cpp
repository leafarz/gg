#include "graphics/drawables/DebugLine.h"

#include <vector>
#include "graphics/Shader.h"

#include "Paths.h"

namespace gg { namespace graphics {
	DebugLine::DebugLine(void)
	{
		m_Shader = new graphics::Shader(ROOT_SHADER + std::string("debugLine.shader"));

		graphics::VertexBufferLayout _layout;
		_layout.push<float>(3);	// position
		_layout.push<float>(4);	// color

		std::vector<uint> _indices = { 0,1 };
		m_IB.setData(&_indices.front(), _indices.size());

		std::vector<float> _sampleVerts = {
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		m_VB.setData(&_sampleVerts.front(), _sampleVerts.size(), true);

		m_VA.init();
		m_VA.addBuffer(m_VB, _layout);
	}

	DebugLine::~DebugLine(void)
	{
	}

	void DebugLine::drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, float thickness)
	{
		std::vector<LineData> _data = { LineData(from, color), LineData(to, color) };

		m_VB.updateData(&_data.front(), _data.size() * sizeof(LineData), true);

		GL(glLineWidth(thickness));
		GL(glDrawElements(GL_LINES, m_IB.getCount(), GL_UNSIGNED_INT, nullptr));
	}

	void DebugLine::drawLines(const std::vector<LineData>& lineQueue, uint thickness, uint count)
	{
		m_VB.updateData(&lineQueue.front(), count * sizeof(LineData), true);

		GL(glLineWidth(thickness));
		GL(glDrawArrays(GL_LINES, 0, count));
	}
}/*namespace graphics*/ } // namespace gg
