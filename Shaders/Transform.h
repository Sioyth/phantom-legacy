#pragma once
#include <glm.hpp>

class Transform
{
public:

	Transform();

public:

	void Translate(glm::vec3 pos);
	void Translate(float x, float y, float z);

	void Rotate(float angle, glm::vec3 rotAxis);
	void Rotate(float angle, float x, float y, float z);

	void Scale(glm::vec3 scale);
	void Scale(float x, float y, float z);

public:

	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();


private:

	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_position;

	glm::mat4 m_transform;

};