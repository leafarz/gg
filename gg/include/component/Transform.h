#ifndef		GG_TRANSFORM_H
#define		GG_TRANSFORM_H
#pragma once

#include "component/Component.h"

namespace gg
{
	class Transform : public Component
	{
	public:
		Transform(void);
		~Transform(void);

		static ComponentType getStaticType(void) { return ComponentType::Transform; }
		virtual ComponentType getType(void) const override { return getStaticType(); }

	private:
		// TODO: add transform matrix
		// TODO: add loc, rot and scale (or just matrix?)

	}; // class Transform
} // namespace gg

#endif
