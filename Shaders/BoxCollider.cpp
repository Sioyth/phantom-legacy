#include "BoxCollider.h"
#include <iostream>

BoxCollider::BoxCollider(Transform& transform)
{
	m_objectTransform = &transform;
	m_dimensions = glm::vec3(1.0f);

	glm::vec3 position = transform.GetPosition();

	physx::PxScene* scene;
	PxGetPhysics().getScenes(&scene, 1);
	physx::PxMaterial* material = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.6f);

	physx::PxReal density = 1.0f;
	physx::PxQuat quaternion(physx::PxIDENTITY);
	physx::PxTransform physxTransform(physx::PxVec3(position.x, position.y, position.z));
	physx::PxBoxGeometry box(physx::PxVec3(0.5f, 0.5f, 0.5f));
	m_dynamic = physx::PxCreateDynamic(PxGetPhysics(), physxTransform, box, *material, density);

	m_actor = m_dynamic;

	scene->addActor(*m_actor);
}

void BoxCollider::Update()
{

	glm::vec3 p(m_dynamic->getGlobalPose().p.x, m_dynamic->getGlobalPose().p.y, m_dynamic->getGlobalPose().p.x);

	m_transform.SetPosition(p);
	m_objectTransform->SetPosition(p);

}

