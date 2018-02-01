#ifndef		GG_CAMERA_H
#define		GG_CAMERA_H
#pragma once

#include "component/Component.h"

namespace gg
{
	class Camera : public Component
	{
	public:
		Camera(void);
		~Camera(void);

		static ComponentType getStaticType(void) { return ComponentType::Camera; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

		void update(void);

	}; // class Camera
} // namespace gg

#endif
