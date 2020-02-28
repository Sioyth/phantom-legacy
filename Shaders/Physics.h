#pragma once
#include <glm.hpp>

#include "Ray.h"
#include "AABB.h"
#include "Time.h"
#include "RayCastHit.h"
#include "SphereCollider.h"

#include <PxPhysicsAPI.h>

namespace Physics
{
	
	void SimulatePhysics();
	bool InitializePhysics();
	
	bool Raycast(Ray& ray, RayCastHit& hit ,float maxDistance = 1000.0f);
	bool RayAABBCollision(AABB collider, glm::vec3 rayPost, glm::vec3 rayDir);
	
	physx::PxRigidDynamic* CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity = physx::PxVec3(0));
	
	//#---------------------------------------------------------------- Variables

	static bool m_initialized;
	static physx::PxPvd* m_pvd; // Physx Visual debuger
	static physx::PxScene* m_scene;
	static physx::PxPhysics* m_physics;
	static physx::PxFoundation* m_foundation;
	static physx::PxDefaultAllocator m_allocator;
	static physx::PxDefaultCpuDispatcher* m_dispatcher;
	static physx::PxDefaultErrorCallback m_errorCallback;

};

