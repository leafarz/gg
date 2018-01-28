#ifndef		GG_GAMEOBJECT_H
#define		GG_GAMEOBJECT_H
#pragma once

#include <unordered_map>
#include <vector>
#include "component/Component.h"

namespace gg
{
	class Transform;
	class GameObject
	{
	public:
		GameObject(const std::string& name = "GameObject");
		~GameObject(void);

		const std::string& getName(void) const;

		void setParent(GameObject* parent);
		GameObject* getParent(void) const;

		void addChild(GameObject* gameObject);
		GameObject* getChild(const std::string& name) const;
		// TODO: add get children

		// TODO: change to template
		void addComponent(Component* component);

		// TODO: add get component
		// TODO: add get components
		// use unordered_multimap::equal_range?

		Transform* getTransform(void) const;

	private:
		std::string m_Name;
		Transform* m_Transform;
		GameObject* m_Parent;
		std::vector<GameObject*> m_Children;
		std::unordered_multimap<ComponentType, Component*> m_Components;
		
	}; // class GameObject
} // namespace gg

#endif
