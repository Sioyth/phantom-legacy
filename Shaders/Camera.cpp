#include "Camera.h"
#include "Screen.h"

Camera::Camera()
{
	m_lookAt = glm::mat4(1.0f);
	m_proj = glm::mat4(1.0f);
	m_target = glm::vec3(0.0f, 0.0, -1.0f);

	m_fov = 45;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;

	m_aspectRatio = (float)Screen::Instance()->GetScreenWidth() / 
					(float)Screen::Instance()->GetScreenHeight();
}

void Camera::LookAt()
{
	m_lookAt = glm::lookAt(m_transform.GetPosition(),
						  m_transform.GetPosition() + m_target,
						  glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::Projection()
{
	m_proj = glm::perspective(m_fov, m_aspectRatio, m_nearClip, m_farClip);
}

const glm::mat4& Camera::GetLookAt()
{
	return m_lookAt;
}

const glm::mat4& Camera::GetProjection()
{
	return m_proj;
}
