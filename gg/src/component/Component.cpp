#include "component/Component.h"

namespace gg
{
	Component::Component(void)
	{
	}

	Component::~Component(void)
	{
	}
	GameObject * Component::getGameObject(void) const
	{
		return m_GameObject;
	}
} // namespace gg
