#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include "Debug.h"

Transform::Transform()
{
	m_scale = glm::vec3(0.0f);
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);

	m_transform = glm::mat4x4(1.0f);
}

void Transform::Translate(glm::vec3 translation)
{
	m_position += translation;
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

const glm::vec3& Transform::GetRotation()
{
	return m_rotation;
}

const glm::vec3& Transform::GetScale()
{
	return m_scale;
}

const glm::mat4x4& Transform::GetTransformMatrix()
{
	return m_transform;
}
