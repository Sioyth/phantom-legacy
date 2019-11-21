#include "Physics.h"
#include <gtx/intersect.hpp>
#include "Debug.h"

bool Physics::RaySphereCollision(SphereCollider sphereCollider, glm::vec3 rayStart, glm::vec3 rayDir)
{
	// Used to store the normal and position of the collision
	glm::vec3 normal;
	glm::vec3 position;

	// Calculates Intersection
	if (glm::intersectRaySphere(rayStart, rayDir, sphereCollider.GetPosition(), sphereCollider.GetRadius(), position, normal))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Physics::RayAABBCollision(AABB collider, glm::vec3 rayPost, glm::vec3 rayDir)
{
	float t;
	glm::vec3 dirfrac;

	//
	dirfrac.x = 1.0f / rayDir.x;
	dirfrac.y = 1.0f / rayDir.y;
	dirfrac.z = 1.0f / rayDir.z;

	// 
	float t1 = (collider.GetMin().x - rayPost.x) * dirfrac.x;
	float t2 = (collider.GetMax().x - rayPost.x) * dirfrac.x;
	float t3 = (collider.GetMin().y - rayPost.y) * dirfrac.y;
	float t4 = (collider.GetMax().y - rayPost.y) * dirfrac.y;
	float t5 = (collider.GetMin().z - rayPost.z) * dirfrac.z;
	float t6 = (collider.GetMax().z - rayPost.z) * dirfrac.z;

	float tmin = glm::max(glm::max(glm::min(t1, t2), glm::min(t3, t4)), glm::min(t5, t6));
	float tmax = glm::min(glm::min(glm::max(t1, t2), glm::max(t3, t4)), glm::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		t = tmax;
		return false;
	}

	t = tmin;
	return true;
}
