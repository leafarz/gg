#include "entity/GameObject.h"

namespace gg
{
	GameObject::GameObject(void)
	{
	}

	GameObject::~GameObject(void)
	{
	}

	void GameObject::addComponent(Component* component)
	{
		component->m_GameObject = this;
		m_Components.insert({ component->getType(), component });
	}
} // namespace gg
