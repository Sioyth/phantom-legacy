#include "Transform.h"
#include <gtc/matrix_transform.hpp>

Transform::Transform()
{
	
}

void Transform::Translate(glm::vec3 translation)
{
	m_transform = glm::translate(glm::mat4(1.0f), translation);
}

void Transform::Translate(float x, float y, float z)
{
	glm::vec3 translation = glm::vec3(x, y, z);
	m_transform = glm::translate(glm::mat4(1.0f), translation);
}

void Transform::Rotate(float angle, glm::vec3 rotAxis)
{
	m_transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), rotAxis);
}

const glm::vec3& Transform::GetPosition()
{
	return m_position;
}
