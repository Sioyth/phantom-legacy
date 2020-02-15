#include "PhantomPhysX.h"
#include <iostream>

#define PVD_HOST "127.0.0.1"

void PhantomPhysx::SimulatePhysics()
{
	m_scene->simulate(1.0f / 60.0f);
	m_scene->fetchResults(true);
}

bool PhantomPhysx::InitializePhysics()
{
	// -------------------------------------------# Setup Dear PhysX context

	m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_allocator, m_errorCallback);

	if (!m_foundation)
	{
		std::cout << "PxCreate Foundation Failed!";
		return false;
	}

	m_pvd = PxCreatePvd(*m_foundation);
	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	m_pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, physx::PxTolerancesScale(), true, m_pvd);

	if (!m_physics)
	{
		std::cout << "PxCreate Physics Failed!";
		return false;
	}

	// do in scene 
	physx::PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	m_dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	m_scene = m_physics->createScene(sceneDesc);

	if (!m_scene)
		std::cout << "PxCreate Scene Failed!";

	//====== PROTOTYPE

	physx::PxMaterial* gMaterial = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_physics, physx::PxPlane(0, 1, 0, 0), *gMaterial);

	m_scene->addActor(*groundPlane);

	if (!groundPlane)
		std::cout << "PxCreate Ground Plane Failed!";

	float j = 2;
	//for (int i = 0; i < 1; i++)
	{
		j += 0.5f;
		physx::PxReal density = 1.0f;
		physx::PxQuat quaternion(physx::PxIDENTITY);
		physx::PxTransform transform(physx::PxVec3(0.0f, j, 0.0f));
		physx::PxBoxGeometry box(physx::PxVec3(0.5f, 0.5f, 0.5f));
		physx::PxRigidDynamic* boxActor = physx::PxCreateDynamic(*m_physics, transform, box, *gMaterial, density);

		boxActor->setAngularDamping(0.75);
		boxActor->setLinearVelocity(physx::PxVec3(0, 0, 0));

		if (!boxActor)
			std::cout << "Box Actor Failed!";

		m_scene->addActor(*boxActor);

	}

	return true;
}

physx::PxRigidDynamic* PhantomPhysx::CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity)
{
	physx::PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidDynamic* dynamic = physx::PxCreateDynamic(*m_physics, t, geometry, *material , 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	m_scene->addActor(*dynamic);
	return dynamic;
}
