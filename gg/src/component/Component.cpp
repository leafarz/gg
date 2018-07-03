#include "component/Component.h"
#include "entity/GameObject.h"
namespace gg
{
	Component::Component(void)
	{
	}

	Component::~Component(void)
	{
		// this should be deleted in the Scene class
		m_GameObject = nullptr;
	}
} // namespace gg
