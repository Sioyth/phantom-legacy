#pragma once

typedef void* EntityHandle;
#define NULL_ENTITY_HANDLE nullptr;

class IComponent
{
public:

	static size_t NextID(); // Turn this into a family generator or generalazion index
	EntityHandle m_entityID = NULL_ENTITY_HANDLE;
};

