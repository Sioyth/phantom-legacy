#include "EmptyGameObject.h"
#include "Debug.h"

EmptyGameObject::EmptyGameObject()
{
	m_collider.SetDimension(glm::vec3(0.8f));
}

void EmptyGameObject::Create()
{
	m_model = new Model;
}

void EmptyGameObject::Render()
{

	m_collider.SetPosition(m_transform.GetPosition());
	m_collider.CalculateMinMax();

	if (m_model)
	{
		m_model->Update();
		m_model->Draw();
	}
}
