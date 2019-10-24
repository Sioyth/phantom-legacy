#include "Camera.h"
#include "Screen.h"
#include "Input.h"

Camera::Camera()
{
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	m_velocity = 0.05f;
	m_sensitivity = 0.2f;

	m_fov = 45;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_aspectRatio = (float)Screen::Instance()->GetScreenWidth() / 
					(float)Screen::Instance()->GetScreenHeight();
}

void Camera::SetOrthoView()
{
	// Set Depth test flag for clear buffer
	Screen::Instance()->SetDepthTest(false);

	// Disable 
	glDisable(GL_DEPTH_TEST);

	// Ortographic view
	m_projectionMatrix = glm::ortho(0.0f, (GLfloat)Screen::Instance()->GetScreenWidth(), 0.0f, (GLfloat)Screen::Instance()->GetScreenHeight());

}

void Camera::SetPerspectiveView()
{
	// Set Depth test flag for clear buffer
	Screen::Instance()->SetDepthTest(true);

	// Enable Depth for 3d so quads don't overlap.
	glEnable(GL_DEPTH_TEST);

	m_aspectRatio = (GLfloat)Screen::Instance()->GetScreenWidth() /
					(GLfloat)Screen::Instance()->GetScreenHeight();

	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);

	// Pass projection matrix to the shaders.
	m_shader.BindUniform("proj");
	m_shader.SendUniformData("proj", 1, GL_FALSE, m_projectionMatrix);
}

void Camera::CalulateLookAt()
{
	m_viewMatrix = glm::lookAt(m_transform.GetPosition(),
						  m_transform.GetPosition() + m_forward,
						  glm::vec3(0.0f, 1.0f, 0.0f));

	// pass view matrix to the shaders
	m_shader.BindUniform("view");
	m_shader.SendUniformData("view", 1, GL_FALSE, m_viewMatrix);
}

void Camera::Projection()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearClip, m_farClip);
}

const glm::mat4& Camera::GetLookAt()
{
	return m_viewMatrix;
}

const glm::mat4& Camera::GetProjection()
{
	return m_projectionMatrix;
}
