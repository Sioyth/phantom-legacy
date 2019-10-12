#pragma once
#include <glm.hpp>

class Transform
{

public:

	void Translate(glm::vec3 pos);
	void Translate(float x, float y, float z);

	void Rotate(glm::vec3 rot);
	void Rotate(float x, float y, float z);

	void Scale(glm::vec3 scale);
	void Scale(float x, float y, float z);

private:

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

};

