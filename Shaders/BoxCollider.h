#pragma once
#include "Collider.h"
#include <glm.hpp>

class BoxCollider : public Collider
{
public:

	BoxCollider() {};
	BoxCollider(GameObject &obj);

	void Update();

	inline void SetMass(float m) { m_dynamic->setMass(m); }

private:

	glm::vec3 m_dimensions;
	physx::PxRigidDynamic* m_dynamic;
};

