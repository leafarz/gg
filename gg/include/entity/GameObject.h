#ifndef		GG_GAMEOBJECT_H
#define		GG_GAMEOBJECT_H
#pragma once

#include <unordered_map>
#include "component/Component.h"

namespace gg
{
	class Transform;
	class GameObject
	{
	public:
		GameObject(void);
		~GameObject(void);

		void addComponent(Component* component);
		// TODO: add get component
		// TODO: add get components
		// use unordered_multimap::equal_range?

	private:
		Transform* m_Transform;
		std::unordered_multimap<ComponentType, Component*> m_Components;
		
	}; // class GameObject
} // namespace gg

#endif
