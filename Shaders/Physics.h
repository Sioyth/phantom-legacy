#pragma once
#include <glm.hpp>

#include "SphereCollider.h"
#include "AABB.h"
#include "Time.h"

#include <PxPhysicsAPI.h>


class Physics
{

public:

	static void SimulatePhysics();
	static bool InitializePhysics();

	static bool RaySphereCollision(SphereCollider sphereCollider, glm::vec3 rayPos, glm::vec3 rayDir);
	static bool RayAABBCollision(AABB collider, glm::vec3 rayPost, glm::vec3 rayDir);

private:

	 bool m_initialized;

	static physx::PxPvd* m_pvd; // Physx Visual debuger
	static physx::PxScene* m_scene;
	static physx::PxPhysics* m_physics;
	static physx::PxFoundation* m_foundation;
	static physx::PxDefaultAllocator m_allocator;
	static physx::PxDefaultCpuDispatcher* m_dispatcher;
	static physx::PxDefaultErrorCallback m_errorCallback;
};

