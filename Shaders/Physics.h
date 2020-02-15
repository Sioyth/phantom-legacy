#pragma once
#include <glm.hpp>

#include "SphereCollider.h"
#include "AABB.h"
#include "Time.h"

#include "PhantomPhysx.h"

class Physics
{

public:

	static void SimulatePhysics();
	static bool InitializePhysics();

	static bool RaySphereCollision(SphereCollider sphereCollider, glm::vec3 rayPos, glm::vec3 rayDir);
	static bool RayAABBCollision(AABB collider, glm::vec3 rayPost, glm::vec3 rayDir);

private:

	 bool m_initialized;
	 
};

