#include "IComponent.h"

static size_t ComponentID = 0;

size_t IComponent::NextID()
{
	return ComponentID++;
}
