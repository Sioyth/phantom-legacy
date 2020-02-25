#include "Ray.h"
#include "Screen.h"
#include "Input.h"

//-----------------------------------------------------------------------------
Ray::Ray(const glm::vec3& origin, const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	// Stores origin of the ray.
	m_origin = origin;

	glm::vec2 mousePosition = Input::Instance()->GetMousePosition();
	float height = (float)Screen::Instance()->GetScreenHeight();
	float width = (float)Screen::Instance()->GetScreenWidth();

	// Normalized Ray
	glm::vec3 ray;
	ray.x = (2.0f * mousePosition.x) / width - 1.0f;
	ray.y = 1.0f - (2.0f * mousePosition.y) / height;
	ray.z = 1.0f;

	// Convert into clip spaces
	glm::vec4 rayClipCoords = glm::vec4(ray.x, ray.y, -1.0f, 1.0f);

	// Inverse Projection Matrix
	glm::mat4 invertedProjectionMatrix = glm::inverse(projectionMatrix);

	// Convert it to eye Space
	glm::vec4 rayEyeCoords = invertedProjectionMatrix * rayClipCoords;
	rayEyeCoords.z = -1.0f;
	rayEyeCoords.w = 0.0f;

	// Inverse Projection Matrix
	glm::mat4 invertedViewMatrix = glm::inverse(viewMatrix);

	// Convert to world coords (ray direction)
	m_direction = invertedViewMatrix * rayEyeCoords;

	// Normalize / Ray Direction
	m_direction = glm::normalize(m_direction);
}

//-----------------------------------------------------------------------------
const glm::vec3& Ray::GetOrigin()
{
	return m_origin;
}

//-----------------------------------------------------------------------------
const glm::vec3& Ray::GetDirection()
{
	return m_direction;
}
