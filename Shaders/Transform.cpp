#include "Transform.h"
#include <gtc/matrix_transform.hpp>

#include "Debug.h"
#include "glad/glad.h"

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
	m_transform = glm::rotate(m_transform, glm::radians(angle), rotAxis);
}

void Transform::Scale(glm::vec3 scale)
{
	m_transform = glm::scale(m_transform, scale);
}

void Transform::Scale(float x, float y, float z)
{
	glm::vec3 scale(x, y, z);
	m_transform = glm::scale(m_transform, scale);
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

void Transform::Render()
{
	//glm::vec3 xLine = glm::vec3(1.0f, 0.0f, 0.0f);
	//glm::vec3 yLine = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 zLine = glm::vec3(0.0f, 0.0f, 1.0f);

	float offset = 5.0f;

	GLfloat xLine[] = { m_position.x, m_position.y, m_position.z,
					m_position.x + offset, m_position.y, m_position.z };

	GLfloat yLine[] = { m_position.x, m_position.y, m_position.z,
					m_position.x, m_position.y + offset, m_position.z };

	GLfloat zLine[] = { m_position.x, m_position.y, m_position.z,
					m_position.x, m_position.y, m_position.z + offset };

	GLfloat xColor[] = { m_position.x, m_position.y, m_position.z,
					m_position.x + offset, m_position.y, m_position.z };

	GLfloat yColor[] = { m_position.x, m_position.y, m_position.z,
					m_position.x, m_position.y + offset, m_position.z };

	GLfloat zColor[] = { m_position.x, m_position.y, m_position.z,
					m_position.x, m_position.y, m_position.z + offset };

	GLuint m_VAO;
	GLuint m_colorVBO;
	GLuint m_vertexVBO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_colorVBO);
	glGenBuffers(1, &m_vertexVBO);

	glBindVertexArray(m_VAO);
	/*{
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(xLine), xLine , GL_DYNAMIC_DRAW);
		glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(m_vertexAttributeID);
	}*/



	//glDrawArrays(GL_LINE, );
}
