#include "Physics.h"
#include <gtx/intersect.hpp>
#include "Debug.h"

#define PVD_HOST "127.0.0.1"

//-----------------------------------------------------------------------------
bool Physics::Raycast(Ray& ray, RayCastHit& hit, float maxDistance)
{
	physx::PxRaycastBuffer hitBuffer;

	physx::PxVec3 o(ray.GetOrigin().x, ray.GetOrigin().y, ray.GetOrigin().z);
	physx::PxVec3 d(ray.GetDirection().x, ray.GetDirection().y, ray.GetDirection().z);

	if (!m_scene->raycast(o, d, maxDistance, hitBuffer))
		return false;
	
	physx::PxRigidDynamic* pickedActor = hitBuffer.getAnyHit(0).actor->is<physx::PxRigidDynamic>();

	if(pickedActor && pickedActor->userData != nullptr)
		hit.SetGameObject(pickedActor->userData);

	return true;
}

//-----------------------------------------------------------------------------
void Physics::SimulatePhysics()
{
	m_scene->simulate(1.0f / 60.0f);
	m_scene->fetchResults(true);
}

//-----------------------------------------------------------------------------
bool Physics::InitializePhysics()
{
	// -------------------------------------------# Setup PhysX context

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

	if (!PxInitExtensions(*m_physics, m_pvd))
		std::cout << "Px Extensions Failed!";

	// do in scene 
	physx::PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
	m_dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = m_dispatcher;
	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	m_scene = m_physics->createScene(sceneDesc);

	if (!m_scene)
		std::cout << "PxCreate Scene Failed!";

	//-----------------------------
	m_scene->getScenePvdClient()->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);

	//====== PROTOTYPE

	physx::PxMaterial* gMaterial = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = physx::PxCreatePlane(*m_physics, physx::PxPlane(0, 1, 0, 0), *gMaterial);

	m_scene->addActor(*groundPlane);

	if (!groundPlane)
		std::cout << "PxCreate Ground Plane Failed!";

	return true;
}

//-----------------------------------------------------------------------------
physx::PxRigidDynamic* Physics::CreateDynamic(const physx::PxTransform& t, const physx::PxGeometry& geometry, const physx::PxVec3& velocity)
{
	physx::PxMaterial* material = m_physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidDynamic* dynamic = physx::PxCreateDynamic(*m_physics, t, geometry, *material, 10.0f);
	dynamic->setAngularDamping(0.5f);
	dynamic->setLinearVelocity(velocity);
	m_scene->addActor(*dynamic);
	return dynamic;
}

physx::PxRigidDynamic* Physics::GetPickActor()
{
	return m_pickActor;
}

//-----------------------------------------------------------------------------
bool Physics::PickObject(Ray& ray, RayCastHit& hit)
{
	float distance = 1000.0f;

	physx::PxRaycastBuffer hitBuffer;

	physx::PxVec3 o(ray.GetOrigin().x, ray.GetOrigin().y, ray.GetOrigin().z);
	physx::PxVec3 d(ray.GetDirection().x, ray.GetDirection().y, ray.GetDirection().z);

	if (!m_scene->raycast(o, d, distance, hitBuffer))
		return false;

	distance = hitBuffer.getAnyHit(0).distance;
	physx::PxRigidDynamic* pickedActor = hitBuffer.getAnyHit(0).actor->is<physx::PxRigidDynamic>();

	if (!pickedActor)
		return false;

	pickedActor->wakeUp();

	// Store gameobject in HitCallback.
	if (pickedActor->userData != nullptr)
		hit.SetGameObject(pickedActor->userData);

	m_pickPos = o + d * distance;
	m_pickActor = PxGetPhysics().createRigidDynamic(physx::PxTransform(m_pickPos));
	m_pickActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);

	physx::PxScene* scene;
	PxGetPhysics().getScenes(&scene, 1);
	scene->addActor(*m_pickActor);

	//local pos = physx::PxVec3(0.f);
	m_pickJoint = PxD6JointCreate(PxGetPhysics(), m_pickActor, physx::PxTransform(physx::PxIdentity), pickedActor, physx::PxTransform(pickedActor->getGlobalPose().transformInv(m_pickPos)));

	if (m_pickJoint)
	{
		m_pickJoint->setMotion(physx::PxD6Axis::eSWING1, physx::PxD6Motion::eFREE);
		m_pickJoint->setMotion(physx::PxD6Axis::eSWING2, physx::PxD6Motion::eFREE);
		m_pickJoint->setMotion(physx::PxD6Axis::eTWIST, physx::PxD6Motion::eFREE);
	}

	m_pickDepth = distance;

	Debug::Log(pickedActor->getMass());

	return true;
}

//-----------------------------------------------------------------------------
void Physics::PickMove(Ray& ray)
{
	if (!m_pickActor)
		return;

	physx::PxVec3 o(ray.GetOrigin().x, ray.GetOrigin().y, ray.GetOrigin().z);
	physx::PxVec3 d(ray.GetDirection().x, ray.GetDirection().y, ray.GetDirection().z);

	m_pickPos = o + d * m_pickDepth;
	m_pickActor->setKinematicTarget(physx::PxTransform(m_pickPos));
}

//-----------------------------------------------------------------------------
void Physics::PickRealease()
{
	if (m_pickJoint)
		m_pickJoint->release();

	m_pickJoint = NULL;

	if (m_pickActor)
		m_pickActor->release();

	m_pickActor = NULL;
}

//-----------------------------------------------------------------------------
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
