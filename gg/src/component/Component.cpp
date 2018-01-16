#include "component/Component.h"
#include "entity/GameObject.h"
namespace gg
{
	Component::Component(void)
	{
	}

	Component::~Component(void)
	{
		delete m_GameObject;
	}

	GameObject* Component::getGameObject(void) const
	{
		return m_GameObject;
	}
} // namespace gg
