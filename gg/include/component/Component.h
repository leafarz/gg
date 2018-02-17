#ifndef		GG_COMPONENT_H
#define		GG_COMPONENT_H
#pragma once

#include "component/ComponentType.h"

namespace gg
{
	class GameObject;
	class Component
	{
	private:
		friend class GameObject;

	public:
		Component(void);
		~Component(void);

		GameObject* getGameObject(void) const;

		virtual ComponentType getType(void) const { return ComponentType::None; }

	protected:
		// This value is null in constructor.
		// It will only be set after GameObject::addComponent() function is called.
		GameObject* m_GameObject = nullptr;
	}; // class Component
} // namespace gg

#endif
