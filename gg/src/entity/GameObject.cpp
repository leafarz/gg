#include "entity/GameObject.h"

#include "component/Transform.h"

#include "util/Iterators.h"

namespace gg
{
	GameObject::GameObject(const std::string& name)
		: m_Name(name),
		m_Transform(new Transform())
	{}

	GameObject::~GameObject(void)
	{
		delete m_Transform;
		FORU(i, 0, m_Children.size()) { delete m_Children[i]; }

		FORU(i, 0, (int)ComponentType::MAX)
		{
			auto _range = m_Components.equal_range((ComponentType)i);
			for (auto it = _range.first; it != _range.second; ++it)
			{
				delete &it;
			}
		}
	}

	const std::string& GameObject::getName(void) const
	{
		return m_Name;
	}

	void GameObject::setParent(GameObject* parent)
	{
		if (m_Parent != nullptr)
		{
			m_Parent->m_ChildCount--;
		}
		m_Parent = parent;
		parent->m_ChildCount++;
	}

	GameObject* GameObject::getParent(void) const
	{
		return m_Parent;
	}

	void GameObject::addChild(GameObject* gameObject)
	{
		if (gameObject->m_Parent != nullptr)
		{
			gameObject->m_Parent->m_ChildCount--;
		}
		m_ChildCount++;
		m_Children.push_back(gameObject);
		gameObject->m_Parent = this;
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

	GameObject* GameObject::getChild(uint index) const
	{
		if (index >= m_ChildCount) { return nullptr; }
		return m_Children[0];
	}

	const std::vector<GameObject*>& GameObject::getChildren(void) const { return m_Children; }

	uint GameObject::getChildCount(void) const { return m_ChildCount; }

	void GameObject::addComponent(Component* component)
	{
		m_Components.insert({ component->getType(), component });
		component->m_GameObject = this;
	}

	Transform* const GameObject::getTransform(void) const
	{
		return m_Transform;
	}
	void GameObject::onInit(void)
	{ }
	void GameObject::onFixedUpdate(void)
	{ }
	void GameObject::onUpdate(void)
	{ }
} // namespace gg
