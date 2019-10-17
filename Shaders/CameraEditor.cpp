#include "CameraEditor.h"
#include "Screen.h"

CameraEditor::CameraEditor()
{

	m_fov = 45;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_forward = glm::vec3(0.0f, 0.0, -1.0f);

	m_aspectRatio = (float)Screen::Instance()->GetScreenWidth() /
					(float)Screen::Instance()->GetScreenHeight();
}

