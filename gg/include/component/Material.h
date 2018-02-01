#ifndef		GG_MATERIAL_H
#define		GG_MATERIAL_H
#pragma once

#include "component/Component.h"
namespace gg
{
	class Material : public Component
	{
	public:
		Material(void);
		~Material(void);

		static ComponentType getStaticType(void) { return ComponentType::Material; }
		virtual ComponentType getType(void) const override { return getStaticType(); }
	}; // class Material
} // namespace gg

#endif
