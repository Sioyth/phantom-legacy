#pragma once

#include <PxPhysicsAPI.h>



namespace PhantomPhysx
{

	void SimulatePhysics();
	bool InitializePhysics();

	physx::PxRigidDynamic* CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity = physx::PxVec3(0));

	
	static physx::PxPvd* m_pvd; // Physx Visual debuger
	static physx::PxScene* m_scene;
	static physx::PxPhysics* m_physics;
	static physx::PxFoundation* m_foundation;
	static physx::PxDefaultAllocator m_allocator;
	static physx::PxDefaultCpuDispatcher* m_dispatcher;
	static physx::PxDefaultErrorCallback m_errorCallback;
};

