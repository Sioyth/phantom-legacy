#include "Physics.h"
#include <gtx/intersect.hpp>
#include "Debug.h"

#define PVD_HOST "127.0.0.1"

physx::PxPvd* Physics::m_pvd;
physx::PxScene* Physics::m_scene;
physx::PxPhysics* Physics::m_physics;
physx::PxFoundation* Physics::m_foundation;
physx::PxDefaultAllocator Physics::m_allocator;
physx::PxDefaultCpuDispatcher* Physics::m_dispatcher;
physx::PxDefaultErrorCallback Physics::m_errorCallback;

void Physics::SimulatePhysics()
{
	m_scene->simulate(1.0f / 60.0f);
	m_scene->fetchResults(true);
}

bool Physics::InitializePhysics()
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
	for (int i = 0; i < 1; i++)
	{
		//j += 1.5f;
		physx::PxReal density = 1.0f;
		physx::PxQuat quaternion(physx::PxIDENTITY);
		physx::PxTransform transform(physx::PxVec3(0.0f, 10, 0.0f));
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
