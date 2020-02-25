#pragma once
#include "Transform.h"
#include "Component.h"
#include "GameObject.h"

#include <PxPhysicsAPI.h>

class Collider : public Component
{
public:

	void Update() = 0;

protected:

	bool m_draw;
	bool m_trigger;

	Transform m_transform;
	GameObject* m_gameObject;

	physx::PxActor* m_actor;
};

