#include "Camera.h"
#include "Screen.h"
#include "Input.h"

Camera::Camera()
{
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);

	m_velocity = 0.05f;
	m_sensitivity = 0.5f;

	m_fov = 45;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;

	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_aspectRatio = (float)Screen::Instance()->GetScreenWidth() / 
					(float)Screen::Instance()->GetScreenHeight();
}

void Camera::Update()
{

	glm::ivec2 mouseMotion;

	mouseMotion = Input::Instance()->GetMouseMotion();

	static GLfloat yaw = -90.0f;
	static GLfloat pitch = 0.0f;

	yaw += mouseMotion.x * m_sensitivity;
	pitch += -mouseMotion.y * m_sensitivity;

	m_forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	m_forward.y = glm::sin(glm::radians(pitch));
	m_forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

	// Get key states
	KeyState keyStates = Input::Instance()->GetKeyStates();

	if (keyStates[SDL_SCANCODE_W])
	{
		m_transform.Translate(m_forward * m_velocity);
	}

	if (keyStates[SDL_SCANCODE_S])
	{
		m_transform.Translate(-m_forward * m_velocity);
	}

	if (keyStates[SDL_SCANCODE_A])
	{
		m_transform.Translate(-glm::normalize(glm::cross(m_forward, m_up)) * m_velocity);
	}

	if (keyStates[SDL_SCANCODE_D])
	{
		m_transform.Translate(glm::normalize(glm::cross(m_forward, m_up)) * m_velocity);
	}

	if (keyStates[SDL_SCANCODE_Q])
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));

		m_transform.Translate(up * m_velocity);
	}

	if (keyStates[SDL_SCANCODE_E])
	{
		glm::vec3 right = glm::cross(m_forward, m_up);
		glm::vec3 up = glm::normalize(glm::cross(m_forward, right));

		m_transform.Translate(-up * m_velocity);
	}

	CalulateLookAt();
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
