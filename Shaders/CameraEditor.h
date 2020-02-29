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

private:

	GameObject* m_selectedObject;

};

