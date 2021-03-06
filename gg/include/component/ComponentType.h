#ifndef		GG_COMPONENTTYPE_H
#define		GG_COMPONENTTYPE_H
#pragma once

namespace gg
{
	enum class ComponentType : int
	{
		None = -1,
		Camera,
		Light,
		Mesh,
		MeshRenderer,
		Transform,
		MAX
	};
} // namespace gg

#endif
