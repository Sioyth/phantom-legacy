#pragma once

#include "Scene.h"

#include "Cube.h"
#include "CameraEditor.h"
#include "Grid.h"
#include "Quad.h"
#include "SkyBox.h"
//#include "PointLight.h"
#include "Light.h"

class DefaultScene : public Scene
{
public:

	DefaultScene();

public:

	void Update();
	void Render();

private:

	Quad m_quad;
	Cube m_cube;
	Grid m_grid;
	CameraEditor m_camera;
	SkyBox m_skyBox;
	Light* m_pointLight;
};

