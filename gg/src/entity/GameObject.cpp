#include "entity/GameObject.h"
#include "core/gg.h"
#include "component/ComponentType.h"
#include "component/Transform.h"

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
			auto range = m_Components.equal_range((ComponentType)i);
			for (auto it = range.first; it != range.second; ++it)
			{
				delete &it;
			}
		}
	}

	const std::string& GameObject::getName(void) const
	{
		return m_Name;
	}

	void gg::GameObject::setParent(GameObject* parent)
	{
		m_Parent = parent;
	}

	GameObject* gg::GameObject::getParent(void) const
	{
		return m_Parent;
	}

	void GameObject::addChild(GameObject * gameObject)
	{
		m_Children.push_back(gameObject);
	}

	void GameObject::addComponent(Component * component)
	{
		m_Components.insert({ component->getType(), component });
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

	Transform * gg::GameObject::getTransform(void) const
	{
		return m_Transform;
	}
} // namespace gg
