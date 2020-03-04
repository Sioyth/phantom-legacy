#include "BoxCollider.h"
#include "Debug.h"
#include <gtc/random.hpp>

//-----------------------------------------------------------------------------
BoxCollider::BoxCollider(GameObject& obj)
{
	m_gameObject = &obj;
	m_dimensions = glm::vec3(1.0f);

	glm::vec3 position = m_gameObject->GetPosition();

	physx::PxScene* scene;
	PxGetPhysics().getScenes(&scene, 1);
	physx::PxMaterial* material = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.0f);

	physx::PxReal density = 1.0f;
	physx::PxQuat quaternion(physx::PxIDENTITY);
	physx::PxTransform physxTransform(physx::PxVec3(position.x, position.y, position.z));
	physx::PxBoxGeometry box(physx::PxVec3(0.5f, 0.5f, 0.5f));
	m_dynamic = physx::PxCreateDynamic(PxGetPhysics(), physxTransform, box, *material, density);

	m_actor = m_dynamic;
	m_actor->userData = m_gameObject;
	m_dynamic->userData = m_gameObject;

	m_dynamic->userData;
	
	scene->addActor(*m_actor);
}

//-----------------------------------------------------------------------------
void BoxCollider::Update()
{
	// Only updates them when the actor is not sleeping
	if (m_dynamic->isSleeping())
		return;

	// Converts a physx matrix to a glm one 

	glm::mat4 matrix;
	physx::PxMat44 v44 = m_dynamic->getGlobalPose();

	glm::vec4 col0(v44.column0.x, v44.column0.y, v44.column0.z, v44.column0.w);
	glm::vec4 col1(v44.column1.x, v44.column1.y, v44.column1.z, v44.column1.w);
	glm::vec4 col2(v44.column2.x, v44.column2.y, v44.column2.z, v44.column2.w);
	glm::vec4 col3(v44.column3.x, v44.column3.y, v44.column3.z, v44.column3.w);

	matrix[0] = col0;
	matrix[1] = col1;
	matrix[2] = col2;
	matrix[3] = col3;

	m_transform.SetMatrix(matrix);
	m_gameObject->SetMatrix(matrix);

}

