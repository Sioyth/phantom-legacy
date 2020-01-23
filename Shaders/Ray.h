#pragma once
#include <glm.hpp>

class Ray
{
public:

	Ray();
	Ray(glm::vec3 origin, glm::vec3 direction);
	Ray(const glm::vec3& origin, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

	const glm::vec3& GetDirection();

private:

	glm::vec3 m_origin;
	glm::vec3 m_direction;

};

