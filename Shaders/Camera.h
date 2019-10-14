#pragma once
#include "GameObject.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

// TODO IMPLEMENT 2D MODE.
//// Enable Depth for 3d so quads don't overlap.
//glEnable(GL_DEPTH_TEST);
//
//// Ortographic view
//proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

class Camera : GameObject
{
public:

	Camera();

public:

	void LookAt();
	void Projection();

public:

	const glm::mat4& GetLookAt();
	const glm::mat4& GetProjection();

protected:

	float m_fov;
	float m_farClip;
	float m_nearClip;
	float m_aspectRatio;

	glm::vec3 m_target;

	glm::mat4 m_proj;
	glm::mat4 m_lookAt; //  View Matrix
};

