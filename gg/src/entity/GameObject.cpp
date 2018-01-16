#include "entity/GameObject.h"
#include "core/gg.h"
#include "component/ComponentType.h"
#include "component/Transform.h"

namespace gg
{
	GameObject::GameObject(void)
		: m_Name("GameObject")
	{
	}

	GameObject::GameObject(const std::string& name)
		: m_Name(name)
	{
	}

	GameObject::~GameObject(void)
	{
		delete m_Transform;
		FORU(i, 0, m_Children.size()) { delete m_Children[i]; }

		FORU(i, 0, (int)ComponentType::MAX)
		{
			auto range = m_Components.equal_range((ComponentType)i);
			for (auto it = range.first; it != range.second; ++it)
			{
				delete &it;
			}
		}
	}

	const std::string & GameObject::getName(void) const
	{
		return m_Name;
	}

	void GameObject::addChild(GameObject * gameObject)
	{
		m_Children.push_back(gameObject);
	}

	GameObject* GameObject::getChild(const std::string& name) const
	{
		VFOR(it, m_Children)
		{
			if ((*it)->getName().compare(name) == 0)
			{
				return *it;
			}
		}
		return nullptr;
	}

	void GameObject::addComponent(Component* component)
	{
		component->m_GameObject = this;
		m_Components.insert({ component->getType(), component });
	}
} // namespace gg
