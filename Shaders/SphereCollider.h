#pragma once
#include <glm.hpp>
#include "Collider.h"

class SphereCollider : public Collider
{
public:

	SphereCollider(GameObject& obj);

	void Update();
	void AddForce(glm::vec3 force);
	void SetVelocity(glm::vec3 v);
	inline void SetMass(float m) { m_dynamic->setMass(m); }

private:

	float m_radius;
	physx::PxRigidDynamic* m_dynamic;

};

