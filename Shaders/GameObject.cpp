#include "GameObject.h"
#include "Debug.h"

bool GameObject::LoadTexture(const std::string& filename, const std::string& textureName)
{
	if (m_material.LoadTexture(filename, textureName))
	{
		m_isTextured = true;
		return true;
	}
	else
	{
		m_isTextured = false;
		return false;
	}
}

void GameObject::Translate(const glm::vec3& pos)
{
	m_transform.Translate(pos);
}

void GameObject::Translate(const float& x, const float& y, const float& z)
{
	m_transform.Translate(x, y, z);
}

void GameObject::Rotate(const float& angle, const glm::vec3& rotAxis)
{
	m_transform.Rotate(angle, rotAxis);
}

//void GameObject::Rotate(const float& angle, const float& x, const float& y, const float& z)
//{
//	m_transform.Rotate(angle, x, y, z);
//}

void GameObject::Scale(const glm::vec3& scale)
{
	m_transform.Scale(scale);
}

void GameObject::Scale(const float& x, const float& y, const float& z)
{
	m_transform.Scale(x, y, z);
}

void GameObject::SetMatrix(glm::mat4 matrix)
{
	m_transform.SetMatrix(matrix);
}

void GameObject::LoadModel(const std::string& filename)
{

	if (m_model)
	{
		m_model->Create();

		m_model->SetShininess(1.0f);
		m_model->SetAmbient(1.0f, 1.0f, 1.0f);
		m_model->SetDiffuse(1.0f, 1.0f, 1.0f);
		m_model->SetSpecular(1.0f, 1.0f, 1.0f);
		m_model->SetPosition(m_transform.GetPosition().x, m_transform.GetPosition().y, m_transform.GetPosition().z);

		if (m_model->LoadModel(filename))
		{
			Debug::Log("Model Loaded correctly!");
		}
	}
	else
	{
		m_model = new Model;

		m_model->Create();

		m_model->SetShininess(1.0f);
		m_model->SetAmbient(1.0f, 1.0f, 1.0f);
		m_model->SetDiffuse(1.0f, 1.0f, 1.0f);
		m_model->SetSpecular(1.0f, 1.0f, 1.0f);
		m_model->SetPosition(m_transform.GetPosition().x, m_transform.GetPosition().y, m_transform.GetPosition().z);

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

void GameObject::Selected()
{

	if (m_isSelected)
	{
		if (!m_transformLine)
		{
			// const offset
			const float offset = 1.0f;

			// Create Pointer
			m_transformLine = new TransformLine[3];

			// origin, starting point of the line
			glm::vec3 origin = glm::vec3(0.0f);
			
			// -------------------------------------------# Create Line X Vertex Position

			glm::vec3 pointX = origin;
			pointX.x -= offset;

			glm::vec3 colorX = glm::vec3(1.0f, 0.0f, 0.0f);

			// Calculates midpoint of the 2 vectors to offset the collider by that much, so colliders are in the right spot;
		    m_transformMidPoints[0] = (origin + pointX) / 2.0f;

			m_transformLine[0].SetColliderDimension(glm::vec3(offset, 0.3f, 0.3f));
			m_transformLine[0].Create(origin, pointX, colorX, m_transform.GetPosition());

			// -------------------------------------------# Create Line Y Vertex Position

			glm::vec3 pointY = origin;
			pointY.y += offset;

			glm::vec3 colorY = glm::vec3(0.0f, 1.0f, 0.0f);

			// Calculates midpoint of the 2 vectors to offset the collider by that much, so colliders are in the right spot;
			m_transformMidPoints[1] = (origin + pointY) / 2.0f;

			m_transformLine[1].SetColliderDimension(glm::vec3(0.3f, offset, 0.3f));
			m_transformLine[1].Create(origin, pointY, colorY, m_transform.GetPosition());

			// -------------------------------------------# Create Line Z Vertex Position

			glm::vec3 pointZ = origin;
			pointZ.z += offset;

			glm::vec3 colorZ = glm::vec3(0.0f, 0.0f, 1.0f);

			// Calculates midpoint of the 2 vectors to offset the collider by that much, so colliders are in the right spot;
			m_transformMidPoints[2] = (origin + pointZ) / 2.0f;

			m_transformLine[2].SetColliderDimension(glm::vec3(0.3f, 0.3f, offset));
			m_transformLine[2].Create(origin, pointZ, colorZ, m_transform.GetPosition());
		}
		else
		{
			static const int TRANSFORM_LINES = 3;

			// Render and update all Transform Lines
			for (int i = 0; i < TRANSFORM_LINES; i++)
			{
				m_transformLine[i].Render();
				m_transformLine[i].Update(m_transform.GetPosition() + m_transformMidPoints[i]);
			}

			// origin, starting point of the line
			glm::vec3 origin = glm::vec3(0.0f);

			glm::vec3 pointX = origin;
			pointX.x -= 1.0f;

			glm::vec3 midpointX = (origin + pointX) / 2.0f;

			
		}

	}
}

TransformLine* GameObject::GetTransformLines()
{
	if (m_transformLine)
	{
		return m_transformLine;
	}
}

const glm::mat4& GameObject::GetMatrix()
{
	return m_transform.GetMatrix();
}

const glm::vec3& GameObject::GetAmbient()
{
	return m_material.GetAmbient();
}

const glm::vec3& GameObject::GetDiffuse()
{
	return m_material.GetDiffuse();
}

const glm::vec3& GameObject::GetSpecular()
{
	return m_material.GetSpecular();
}

const glm::vec3& GameObject::GetPosition()
{
	return m_transform.GetPosition();
}

const glm::vec3& GameObject::GetRotation()
{
	return m_transform.GetRotation();
}

const glm::vec3& GameObject::GetScale()
{
	return m_transform.GetScale();
}

const AABB& GameObject::GetTransformLineCollider()
{
	if (m_transformLine)
	{
		return m_transformLine->GetCollider();
	}
}

void GameObject::SetIsLit(bool flag)
{
	m_isLit = flag;
}

bool GameObject::GetIsLit()
{
	return m_isLit;
}

void GameObject::SetPosition(glm::vec3 position)
{
	static const int NUMBER_LINES = 3;

	m_transform.SetPosition(position);

	if (!m_transformLine)
		return;

	for (int i = 0; i < NUMBER_LINES; i++)
	{
		m_transformLine[i].SetPosition(position);
	}
	
}

void GameObject::SetAmbient(glm::vec3 ambient)
{
	m_material.SetAmbient(ambient);
}

void GameObject::SetDiffuse(glm::vec3 diffuse)
{
	return m_material.SetDiffuse(diffuse);
}

void GameObject::SetSpecular(glm::vec3 specular)
{
	m_material.SetSpecular(specular);
}

