#include "GameObject.h"

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

