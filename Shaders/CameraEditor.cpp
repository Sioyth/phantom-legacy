#include "CameraEditor.h"
#include "Screen.h"
#include "Input.h"
#include "Debug.h"

#include "SceneManager.h"
#include "Physics.h"

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
		// TODO RAYCAST CLASS
		// Ray Cast

		m_isMoving = false;

		glm::vec2 mousePosition = Input::Instance()->GetMousePosition();
		float height = (float)Screen::Instance()->GetScreenHeight();
		float width = (float)Screen::Instance()->GetScreenWidth();

		// Normalized Ray
		glm::vec3 ray;
		ray.x = (2.0f * mousePosition.x) / width - 1.0f;
		ray.y = 1.0f - (2.0f * mousePosition.y) / height;
		ray.z = 1.0f;

		// Convert into clip space
		glm::vec4 rayClipCoords = glm::vec4(ray.x, ray.y, -1.0f, 1.0f);

		// Inverse Projection Matrix
		glm::mat4 invertedProjectionMatrix = glm::inverse(m_projectionMatrix);

		// Convert it to eye Space
		glm::vec4 rayEyeCoords = invertedProjectionMatrix * rayClipCoords;
		rayEyeCoords.z = -1.0f;
		rayEyeCoords.w = 0.0f;

		// Inverse Projection Matrix
		glm::mat4 invertedViewMatrix = glm::inverse(m_viewMatrix);

		// Convert to world coords (ray direction)
		glm::vec3 rayWorldCoords = invertedViewMatrix * rayEyeCoords;

		// Normalize / Ray Direction
		rayWorldCoords = glm::normalize(rayWorldCoords);

		//TODO move this out of camera editor class.

		// Checks all objects int he scene to see if it's colliding with it
		for (int i = 0; i < SceneManager::Instance()->GetCurrentScene().GetGameObjects().size(); i++)
		{
			if (Physics::RayAABBCollision(SceneManager::Instance()->GetCurrentScene().GetGameObjects()[i]->GetCollider(), m_transform.GetPosition(), rayWorldCoords))
			{
				if (lastSelectedGameObject > -1)
				{
					// First set last selected object to false
					SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->SetIsSelected(false);
				}

				// Then select the new object
				SceneManager::Instance()->GetCurrentScene().GetGameObjects()[i]->SetIsSelected(true);
				lastSelectedGameObject = i;
			}
			else
			{
				//SceneManager::Instance()->GetCurrentScene().GetGameObjects()[i]->SetIsSelected(false);
			}
		}

		if (lastSelectedGameObject > -1)
		{

			// TODO make this functions, 
			static const int NUMBER_LINES = 3;

			// Check Collision with transform Lines
			if (Physics::RayAABBCollision(SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[0].GetCollider(), m_transform.GetPosition(), rayWorldCoords))
			{
				glm::vec3 translate = glm::vec3(0.0f);
				translate.x = Input::Instance()->GetMouseMotion().x;

				float speed = 0.01f;
				translate *= speed;

				SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->Translate(translate);

				// Translates all lines to follow the object.
				for (int i = 0; i < NUMBER_LINES; i++)
				{
					SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[i].Translate(translate);
				}

				Debug::Log("X - Translation!");
			}

			// Check Collision with transform Lines
			else if (Physics::RayAABBCollision(SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[1].GetCollider(), m_transform.GetPosition(), rayWorldCoords))
			{
				glm::vec3 translate = glm::vec3(0.0f);
				translate.y = -Input::Instance()->GetMouseMotion().y;

				float speed = 0.01f;
				translate *= speed;

				SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->Translate(translate);

				// Translates all lines to follow the object.
				for (int i = 0; i < NUMBER_LINES; i++)
				{
					SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[i].Translate(translate);
				}

				Debug::Log("Y - Translation!");
			}

			// Check Collision with transform Lines
			else if (Physics::RayAABBCollision(SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[2].GetCollider(), m_transform.GetPosition(), rayWorldCoords))
			{
				glm::vec3 translate = glm::vec3(0.0f);
				translate.z = Input::Instance()->GetMouseMotion().x;

				float speed = 0.01f;
				translate *= speed;

				SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->Translate(translate);

				// Translates all lines to follow the object.
				for (int i = 0; i < NUMBER_LINES; i++)
				{
					SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->GetTransformLines()[i].Translate(translate);
				}

				Debug::Log("Z - Translation!");
			}
		}

	}
	else 
	{
		m_isMoving = false;
	}

	if (lastSelectedGameObject > -1)
	{
		// Updates and renders the selected game objects
		SceneManager::Instance()->GetCurrentScene().GetGameObjects()[lastSelectedGameObject]->Selected();
	}

	CalulateLookAt();
}

