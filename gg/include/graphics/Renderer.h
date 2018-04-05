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
		enum class SystemLightIndex : ubyte
		{
			Position,
			Direction,
			Color,
			Intensity,
			ConstantAttenuation,
			LinearAttenuation,
			ExponentAttenuation,
			Angle
		};

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

			void add(const Math::Vec3f& position, const Math::Color& color)
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

			TimedLineData(float duration, const Math::Vec3f& position, const Math::Color& color)
				: duration(duration), lineData({position, color})
			{ }
		};

	public:
		Renderer(void);
		~Renderer(void);

		void begin(void) const;
		void draw(
			GameObject* gameObject,
			const Math::Mat4f& viewMatrix,
			const Math::Mat4f& projectionMatrix,
			const Math::Mat4f& pvMatrix,
			const Math::Vec3f& cameraPosition,
			const Math::Vec3f& cameraDirection,
			const LightSettings& lightSettings,
			const std::vector<Light*>& lights
		);

	/* Light */
	private:
		// MAX_LIGHTS * numOfProperties
		const char* m_SystemLightPrefixes[8 * 8] = {
			"sys_Lights[0].position", "sys_Lights[0].direction", "sys_Lights[0].color", "sys_Lights[0].intensity", "sys_Lights[0].constantAttenuation", "sys_Lights[0].linearAttenuation", "sys_Lights[0].exponentAttenuation", "sys_Lights[0].angle",
			"sys_Lights[1].position", "sys_Lights[1].direction", "sys_Lights[1].color", "sys_Lights[1].intensity", "sys_Lights[1].constantAttenuation", "sys_Lights[1].linearAttenuation", "sys_Lights[1].exponentAttenuation", "sys_Lights[1].angle",
			"sys_Lights[2].position", "sys_Lights[2].direction", "sys_Lights[2].color", "sys_Lights[2].intensity", "sys_Lights[2].constantAttenuation", "sys_Lights[2].linearAttenuation", "sys_Lights[2].exponentAttenuation", "sys_Lights[2].angle",
			"sys_Lights[3].position", "sys_Lights[3].direction", "sys_Lights[3].color", "sys_Lights[3].intensity", "sys_Lights[3].constantAttenuation", "sys_Lights[3].linearAttenuation", "sys_Lights[3].exponentAttenuation", "sys_Lights[3].angle",
			"sys_Lights[4].position", "sys_Lights[4].direction", "sys_Lights[4].color", "sys_Lights[4].intensity", "sys_Lights[4].constantAttenuation", "sys_Lights[4].linearAttenuation", "sys_Lights[4].exponentAttenuation", "sys_Lights[4].angle",
			"sys_Lights[5].position", "sys_Lights[5].direction", "sys_Lights[5].color", "sys_Lights[5].intensity", "sys_Lights[5].constantAttenuation", "sys_Lights[5].linearAttenuation", "sys_Lights[5].exponentAttenuation", "sys_Lights[5].angle",
			"sys_Lights[6].position", "sys_Lights[6].direction", "sys_Lights[6].color", "sys_Lights[6].intensity", "sys_Lights[6].constantAttenuation", "sys_Lights[6].linearAttenuation", "sys_Lights[6].exponentAttenuation", "sys_Lights[6].angle",
			"sys_Lights[7].position", "sys_Lights[7].direction", "sys_Lights[7].color", "sys_Lights[7].intensity", "sys_Lights[7].constantAttenuation", "sys_Lights[7].linearAttenuation", "sys_Lights[7].exponentAttenuation", "sys_Lights[7].angle"
		};


	/* Debug draws */
	public:
		/* Adds line data to queue to be drawn on render. */
		void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color, uint thickness);
		void drawLine(const Math::Vec3f& from, const Math::Vec3f& to, const Math::Color& color, uint thickness, float duration);
		/* Draws all the debugs. */
		void drawDebug(const Math::Mat4f& pvMatrix);

	private:
		graphics::DebugLine* m_DebugLine;
		std::unordered_map<uint, LineDataGroup> m_Buffer;
		std::unordered_map<uint, std::vector<TimedLineData>> m_TimedBuffer;
	}; // class Renderer
}/*namespace graphics*/ } // namespace gg

#endif
