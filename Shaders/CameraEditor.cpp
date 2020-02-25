
#include "Ray.h"
#include "Debug.h"
#include "Input.h"
#include "Screen.h"
#include "RayCastHit.h"
#include "CameraEditor.h"
#include "SceneManager.h"
#include "Interface.h"

CameraEditor::CameraEditor()
{

	m_fov = 45;
	m_nearClip = 0.1f;
	m_farClip = 100.0f;
	m_viewMatrix = glm::mat4(1.0f);
	m_projectionMatrix = glm::mat4(1.0f);
	m_forward = glm::vec3(0.0f, 0.0, -1.0f);

	m_isMoving = false;

	m_aspectRatio = (float)Screen::Instance()->GetScreenWidth() /
					(float)Screen::Instance()->GetScreenHeight();

	m_transform.SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));
	
}

void CameraEditor::Create()
{
	m_material.BindUniform("cameraPosition");
}

void CameraEditor::Update()
{
	static int lastSelectedGameObject = -1; // starting at -1 to check until it has a value

	m_material.SendUniformData("cameraPosition", m_transform.GetPosition());

	if (Input::Instance()->GetMouseButtonDown(1))
	{
		m_isMoving = true;

		glm::ivec2 mouseMotion;

		// Get Mouse Motion
		mouseMotion = Input::Instance()->GetMouseMotion();

		static GLfloat yaw = -90.0f;
		static GLfloat pitch = 0.0f;

		yaw += mouseMotion.x * m_sensitivity;
		pitch += -mouseMotion.y * m_sensitivity;

		m_forward.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
		m_forward.y = glm::sin(glm::radians(pitch));
		m_forward.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

		// Camera Movement
		if (Input::Instance()->KeyDown(Keycode::W))
		{
			m_transform.Translate(m_forward * m_velocity);
		}

		if (Input::Instance()->KeyDown(Keycode::S))
		{
			m_transform.Translate(-m_forward * m_velocity);
		}

		if (Input::Instance()->KeyDown(Keycode::A))
		{
			m_transform.Translate(-glm::normalize(glm::cross(m_forward, m_up)) * m_velocity);
		}

		if (Input::Instance()->KeyDown(Keycode::D))
		{
			m_transform.Translate(glm::normalize(glm::cross(m_forward, m_up)) * m_velocity);
		}

		// Down
		if (Input::Instance()->KeyDown(Keycode::C))
		{
			glm::vec3 right = glm::cross(m_forward, m_up);
			glm::vec3 up = glm::normalize(glm::cross(m_forward, right));

			m_transform.Translate(up * m_velocity);
		}

		// Up
		if (Input::Instance()->KeyDown(Keycode::E))
		{
			glm::vec3 right = glm::cross(m_forward, m_up);
			glm::vec3 up = glm::normalize(glm::cross(m_forward, right));

			m_transform.Translate(-up * m_velocity);
		}
	}
	else if (Input::Instance()->GetMouseButtonDown(0))
	{

		if (!Interface::Instance()->IsMouseOverUI())
			return;
		
		RayCastHit hit;
		m_isMoving = false;
		Ray ray = Ray(m_transform.GetPosition(), m_projectionMatrix, m_viewMatrix);

		if (!SceneManager::Instance()->GetCurrentScene().Raycast(ray, hit, 10000.0f))
			return;

		if (!hit.GetGameObject())
			return;

		m_selectedObject = hit.GetGameObject();
		m_selectedObject->SetIsSelected(true);

		SceneManager::Instance()->GetCurrentScene().SetSelectedObject(m_selectedObject);

	}
	else 
	{
		m_isMoving = false;
	}

	if (m_selectedObject)
		m_selectedObject->Selected();

	CalulateLookAt();
}

