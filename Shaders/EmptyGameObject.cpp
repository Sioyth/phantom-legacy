#include "EmptyGameObject.h"
#include "Debug.h"

EmptyGameObject::EmptyGameObject()
{
}

void EmptyGameObject::Create()
{
	m_model = new Model;
	m_model->Create();

	m_model->SetShininess(1.0f);
	m_model->SetAmbient(1.0f, 1.0f, 1.0f);
	m_model->SetDiffuse(1.0f, 1.0f, 1.0f);
	m_model->SetSpecular(1.0f, 1.0f, 1.0f);
	m_model->SetPosition(m_transform.GetPosition().x, m_transform.GetPosition().y, m_transform.GetPosition().z);
}

void EmptyGameObject::Render()
{
	if (m_model)
	{
		m_model->Update();
		m_model->Draw();
	}
}

void EmptyGameObject::LoadModel(const std::string& filename)
{
	if (m_model)
	{
		if (m_model->LoadModel(filename))
		{
			Debug::Log("Model Loaded correctly!");
		}
	}
	else
	{
		m_model = new Model;

		if (m_model->LoadModel(filename))
		{
			Debug::Log("Model Loaded correctly!");
		}
		else 
		{
			Debug::ErrorLog("Model didn't Loaded correctly!");
		}
	}
}
