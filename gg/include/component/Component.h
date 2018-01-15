#ifndef		GG_COMPONENT_H
#define		GG_COMPONENT_H
#pragma once

#include <string>
#include "component/ComponentType.h"
namespace gg
{
	class GameObject;
	class Component
	{
		friend class GameObject;
	public:
		Component(void);
		~Component(void);

		GameObject* getGameObject(void) const;

		virtual ComponentType getType(void) const { return ComponentType::None; }
	private:
		GameObject* m_GameObject = nullptr;
	}; // class Component
} // namespace gg

#endif
