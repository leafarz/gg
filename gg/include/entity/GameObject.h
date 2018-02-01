#ifndef		GG_GAMEOBJECT_H
#define		GG_GAMEOBJECT_H
#pragma once

#include <unordered_map>
#include <vector>

#include "component/Component.h"
#include "component/Components.h"

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

		void addComponent(Component* component);
		template<class T> T* addComponent()
		{
			T* _component = new T();
			m_Components.insert({ ((Component*)_component)->getType(), _component });
			return _component;
		}

		template<class T> T* getComponent() { static_assert(false); }
		template<> Camera* getComponent<Camera>()
		{
			auto _component = m_Components.find(Camera::getStaticType());
			return (_component == m_Components.end()) ? nullptr : (Camera*)_component->second;
		}
		template<> Material* getComponent<Material>()
		{
			auto _component = m_Components.find(Material::getStaticType());
			return (_component == m_Components.end()) ? nullptr : (Material*)_component->second;
		}
		template<> Mesh* getComponent<Mesh>()
		{
			auto _component = m_Components.find(Mesh::getStaticType());
			return (_component == m_Components.end()) ? nullptr : (Mesh*)_component->second;
		}
		template<> MeshRenderer* getComponent<MeshRenderer>()
		{
			auto _component = m_Components.find(MeshRenderer::getStaticType());
			return (_component == m_Components.end()) ? nullptr : (MeshRenderer*)_component->second;
		}
		template<> Transform* getComponent<Transform>()
		{
			auto _component = m_Components.find(Transform::getStaticType());
			return (_component == m_Components.end()) ? nullptr : (Transform*)_component->second;
		}

		// TODO: add get components
		// use unordered_multimap::equal_range?
		template<class T> std::vector<T*> getComponents()
		{
			return nullptr;
		}

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
