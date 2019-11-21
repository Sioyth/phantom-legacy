#pragma once
#include <glm.hpp>

#include "SphereCollider.h"
#include "AABB.h"

class Physics
{
public:

	static bool RaySphereCollision(SphereCollider sphereCollider, glm::vec3 rayPos, glm::vec3 rayDir);
	static bool RayAABBCollision(AABB collider, glm::vec3 rayPost, glm::vec3 rayDir);
};

