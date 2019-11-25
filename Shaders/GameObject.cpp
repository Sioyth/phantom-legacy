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

void GameObject::Selected()
{

	if (m_isSelected)
	{
		if (!m_transformLine)
		{
			// const offset
			const float offset = 1.0f;

			// Create Pointer
			m_transformLine = new TransformLine(m_transform.GetPosition());

			// origin, starting point of the line
			glm::vec3 origin = glm::vec3(0.0f);
			
			// Create Line X Vertex Position
			glm::vec3 pointX = origin;
			pointX.x -= offset;
		
			glm::vec3 colorX = glm::vec3(1.0f, 0.0f, 0.0f);

			m_transformLine->GetCollider().SetDimension(glm::vec3(offset, 1.0f, 1.0f));
			m_transformLine->Create(origin, pointX, colorX);
		}
		else
		{
			m_transformLine->Render();

			/*if (Input::Instance()->GetMouseButtonDown(0))
			{
				glm::vec3 translate;
				translate.x = Input::Instance()->GetMouseMotion().x;
				translate.y = Input::Instance()->GetMouseMotion().y;
				translate.z = 0.0f;

				m_transform.Translate(translate * 0.01f);
			}*/
		}

	}
}

const AABB& GameObject::GetTransformLineCollider()
{
	if (m_transformLine)
	{
		return m_transformLine->GetCollider();
	}
}

