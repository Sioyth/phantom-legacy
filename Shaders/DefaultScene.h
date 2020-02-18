#pragma once

#include "Scene.h"
#include "Cube.h"
#include "CameraEditor.h"
#include "EmptyGameObject.h"
#include "Grid.h"
#include "Quad.h"
#include "SkyBox.h"
#include "Light.h"

class DefaultScene : public Scene
{
public:

	DefaultScene();

public:

	void Start() {};
	void Update();
	void Render();

private:

	Grid m_grid;
	Quad m_debugPlane;
	CameraEditor m_camera;
	SkyBox m_skyBox;
};

