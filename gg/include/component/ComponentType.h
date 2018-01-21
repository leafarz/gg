#ifndef		GG_COMPONENTTYPE_H
#define		GG_COMPONENTTYPE_H
#pragma once

#include "core/Types.h"
namespace gg
{
	enum class ComponentType : int
	{
		None		= -1,
		Transform,
		Camera,
		MAX
	};
} // namespace gg

#endif
