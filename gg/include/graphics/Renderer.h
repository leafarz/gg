#ifndef		GG_RENDERER_H
#define		GG_RENDERER_H
#pragma once

#include <vector>
#include <unordered_map>

#include "core/Types.h"

#include "graphics/drawables/Drawables.h"
#include "graphics/LightSettings.h"

#include "platform/opengl/GLCommon.h"

#include "math/Mat4f.h"
#include "math/Vec3f.h"
#include "math/Color.h"

namespace gg {
// forward declarations
class Light;
class GameObject;
namespace graphics {
	
	class Renderer
	{
	private:
		enum class SystemLightIndex : uint
		{
			Position			= 0,
			Direction			= 1,
			Color				= 2,
			Intensity			= 3,
			ConstantAttenuation	= 4,
			LinearAttenuation	= 5,
			ExponentAttenuation	= 6,
			Angle				= 7,
			Specular			= 8,
			Length				= 9
		};
#pragma region DEBUG_STRUCTS
		struct LineDataGroup
		{
		private:
			uint count;
			std::vector<DebugLine::LineData> lineData;

		public:
			LineDataGroup(void)
			{ }
			LineDataGroup(const std::vector<DebugLine::LineData>& lineData)
				: lineData(lineData)
			{
				count = lineData.size() - 1;
			}

			uint getCount(void) { return count; }
			void resetCount(void) { count = 0; }
			const std::vector<DebugLine::LineData>& getLineData(void) { return lineData; }

			bool hasSlot(void)
			{
				return count < (lineData.size() - 1);
			}

			void add(const math::Vec3f& position, const math::Color& color)
			{
				if (hasSlot())
				{
					this->lineData[count].position = position;
					this->lineData[count].color = color;
				}
				else
				{
					this->lineData.push_back(DebugLine::LineData(position, color));
				}
				count++;
			}
		};
		struct TimedLineData
		{
			float duration;
			DebugLine::LineData lineData;

			TimedLineData(float duration, const math::Vec3f& position, const math::Color& color)
				: duration(duration), lineData({position, color})
			{ }
		};
#pragma endregion

	public:
		Renderer(void);
		~Renderer(void);

		void begin(void) const;
		void draw(
			GameObject* gameObject,
			const math::Mat4f& viewMatrix,
			const math::Mat4f& projectionMatrix,
			const math::Mat4f& pvMatrix,
			const math::Vec3f& cameraPosition,
			const math::Vec3f& cameraDirection,
			const LightSettings& lightSettings,
			const std::vector<Light*>& lights
		);

	/* Light */
	private:
		// MAX_LIGHTS * numOfProperties
		const char* m_SystemLightPrefixes[8 * (int)SystemLightIndex::Length] = {
			"sys_Lights[0].position", "sys_Lights[0].direction", "sys_Lights[0].color", "sys_Lights[0].intensity", "sys_Lights[0].constantAttenuation", "sys_Lights[0].linearAttenuation", "sys_Lights[0].exponentAttenuation", "sys_Lights[0].angle", "sys_Lights[0].specular",
			"sys_Lights[1].position", "sys_Lights[1].direction", "sys_Lights[1].color", "sys_Lights[1].intensity", "sys_Lights[1].constantAttenuation", "sys_Lights[1].linearAttenuation", "sys_Lights[1].exponentAttenuation", "sys_Lights[1].angle", "sys_Lights[1].specular",
			"sys_Lights[2].position", "sys_Lights[2].direction", "sys_Lights[2].color", "sys_Lights[2].intensity", "sys_Lights[2].constantAttenuation", "sys_Lights[2].linearAttenuation", "sys_Lights[2].exponentAttenuation", "sys_Lights[2].angle", "sys_Lights[2].specular",
			"sys_Lights[3].position", "sys_Lights[3].direction", "sys_Lights[3].color", "sys_Lights[3].intensity", "sys_Lights[3].constantAttenuation", "sys_Lights[3].linearAttenuation", "sys_Lights[3].exponentAttenuation", "sys_Lights[3].angle", "sys_Lights[3].specular",
			"sys_Lights[4].position", "sys_Lights[4].direction", "sys_Lights[4].color", "sys_Lights[4].intensity", "sys_Lights[4].constantAttenuation", "sys_Lights[4].linearAttenuation", "sys_Lights[4].exponentAttenuation", "sys_Lights[4].angle", "sys_Lights[4].specular",
			"sys_Lights[5].position", "sys_Lights[5].direction", "sys_Lights[5].color", "sys_Lights[5].intensity", "sys_Lights[5].constantAttenuation", "sys_Lights[5].linearAttenuation", "sys_Lights[5].exponentAttenuation", "sys_Lights[5].angle", "sys_Lights[5].specular",
			"sys_Lights[6].position", "sys_Lights[6].direction", "sys_Lights[6].color", "sys_Lights[6].intensity", "sys_Lights[6].constantAttenuation", "sys_Lights[6].linearAttenuation", "sys_Lights[6].exponentAttenuation", "sys_Lights[6].angle", "sys_Lights[6].specular",
			"sys_Lights[7].position", "sys_Lights[7].direction", "sys_Lights[7].color", "sys_Lights[7].intensity", "sys_Lights[7].constantAttenuation", "sys_Lights[7].linearAttenuation", "sys_Lights[7].exponentAttenuation", "sys_Lights[7].angle", "sys_Lights[7].specular"
		};


	/* Debug draws */
	public:
		/* Submits line data to queue to be drawn for render. */
		void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, uint thickness);

		/* Submits line data to queue to be drawn for render. */
		void drawLine(const math::Vec3f& from, const math::Vec3f& to, const math::Color& color, uint thickness, float duration);

		/* Draws all the debugs. */
		void drawDebug(const math::Mat4f& pvMatrix);

	private:
		graphics::DebugLine* m_DebugLine;
		std::unordered_map<uint, LineDataGroup> m_LineBuffer;
		std::unordered_map<uint, std::vector<TimedLineData>> m_TimedLineBuffer;
	}; // class Renderer
}/*namespace graphics*/ } // namespace gg

#endif
