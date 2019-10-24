#pragma once
#include "GameObject.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera : public GameObject
{
public:

	Camera();

public:

	enum Origin2D{ TOP_LEFT, BOTTOM_LEFT};

public:

	virtual void Update() {};

public:

	void SetOrthoView();
	void SetPerspectiveView();

public:

	void CalulateLookAt();
	void Projection();

public:

	const glm::mat4& GetLookAt();
	const glm::mat4& GetProjection();

protected:

	GLfloat m_fov;
	GLfloat m_farClip;
	GLfloat m_nearClip;
	GLfloat m_velocity;
	GLfloat m_aspectRatio;
	GLfloat m_sensitivity;

	glm::vec3 m_up;
	glm::vec3 m_forward;

	glm::mat4 m_viewMatrix; 
	glm::mat4 m_projectionMatrix;
};

