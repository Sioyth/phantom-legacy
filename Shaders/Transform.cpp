#include "Transform.h"
#include <gtc/matrix_transform.hpp>

#include "Debug.h"
#include "glad/glad.h"

Transform::Transform()
{
	m_scale = glm::vec3(1.0f);
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);

	m_transform = glm::mat4x4(1.0f);
}

void Transform::Translate(glm::vec3 translation)
{
	m_position += translation;
	m_transform = glm::translate(m_transform, translation);

}

void Transform::Translate(float x, float y, float z)
{
	glm::vec3 translation = glm::vec3(x, y, z);
	m_position += translation;
	m_transform = glm::translate(m_transform, translation);
}

void Transform::Rotate(float angle, glm::vec3 rotAxis)
{
	if (rotAxis == glm::vec3(1.0f, 0.0f, 0.0f))
	{
		/*if(angle > 0 && angle < m_rotation.x)
		{ 
			angle = m_rotation.x - angle;
		}

		if (angle == 0.0f)
		{
			m_rotation.x = -m_rotation.x;
		}*/

		m_rotation.x = angle;
	}

	if (rotAxis == glm::vec3(0.0f, 1.0f, 0.0f))
	{
		m_rotation.y = angle;
	}

	if (rotAxis == glm::vec3(0.0f, 0.0f, 1.0f))
	{
		m_rotation.z = angle;
	}

	m_transform = glm::rotate(m_transform, glm::radians(angle), rotAxis);
}

void Transform::Scale(glm::vec3 scale)
{
	if (scale.x != 1.0f)
	{
		m_scale.x = scale.x;
	}

	if (scale.y != 1.0f)
	{
		m_scale.y = scale.y;
	}

	if (scale.z != 1.0f)
	{
		m_scale.z = scale.z;
	}
	
	//m_scale = scale;
	m_transform = glm::scale(m_transform, scale);
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 scale(x, y, z);
	m_transform = glm::scale(m_transform, scale);
}

void Transform::SetPosition(glm::vec3 position)
{
	m_position = position;
	m_transform = glm::translate(glm::mat4(1.0f), position);
}

void Transform::SetMatrix(glm::mat4 matrix)
{
	m_transform = matrix;
}

const glm::mat4& Transform::GetMatrix()
{
	return m_transform;
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
