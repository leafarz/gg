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

		template<class T> std::vector<T*> getComponents()
		{
			static_assert(false);
			return nullptr;
		}
		template<> std::vector<Camera*> getComponents<Camera>()
		{
			std::vector<Camera*> _components;
			auto _range = m_Components.equal_range(ComponentType::MeshRenderer);

			for (auto it = _range.first; it != _range.second; ++it)
			{
				_components.push_back((Camera*)it->second);
			}
			return _components;
		}
		template<> std::vector<Material*> getComponents<Material>()
		{
			std::vector<Material*> _components;
			auto _range = m_Components.equal_range(ComponentType::MeshRenderer);

			for (auto it = _range.first; it != _range.second; ++it)
			{
				_components.push_back((Material*)it->second);
			}
			return _components;
		}
		template<> std::vector<Mesh*> getComponents<Mesh>()
		{
			std::vector<Mesh*> _components;
			auto _range = m_Components.equal_range(ComponentType::MeshRenderer);

			for (auto it = _range.first; it != _range.second; ++it)
			{
				_components.push_back((Mesh*)it->second);
			}
			return _components;
		}
		template<> std::vector<MeshRenderer*> getComponents<MeshRenderer>()
		{
			std::vector<MeshRenderer*> _components;
			auto _range = m_Components.equal_range(ComponentType::MeshRenderer);

			for (auto it = _range.first; it != _range.second; ++it)
			{
				_components.push_back((MeshRenderer*)it->second);
			}
			return _components;
		}
		template<> std::vector<Transform*> getComponents<Transform>()
		{
			std::vector<Transform*> _components;
			auto _range = m_Components.equal_range(ComponentType::MeshRenderer);

			for (auto it = _range.first; it != _range.second; ++it)
			{
				_components.push_back((Transform*)it->second);
			}
			return _components;
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
