#pragma once
#include "Collider.h"
#include <glm.hpp>

class BoxCollider : public Collider
{
public:

	BoxCollider() {};
	BoxCollider(Transform & transform);

	void Update();

private:

	glm::vec3 m_dimensions;
	physx::PxRigidDynamic* m_dynamic;
};

