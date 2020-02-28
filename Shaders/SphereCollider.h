#pragma once
#include <glm.hpp>
#include "Collider.h"

class SphereCollider : public Collider
{
public:

	SphereCollider(GameObject& obj);

	void Update();


private:

	float m_radius;
	physx::PxRigidDynamic* m_dynamic;

};

