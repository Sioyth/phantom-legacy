#pragma once
#include "Camera.h"

class CameraEditor : public Camera
{

public:

	CameraEditor();

public:

	void Update();
	void Render() {};
	void Create();

	void CameraMovement();
	void MousePicking();

	glm::vec3 GetForwardVector();

private:

	GameObject* m_selectedObject;

};

