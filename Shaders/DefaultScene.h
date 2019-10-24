#pragma once

#include "Scene.h"

#include "Cube.h"
#include "CameraEditor.h"
#include "Grid.h"

class DefaultScene : public Scene
{
public:

	DefaultScene();

public:

	void Update();
	void Render();

private:

	Cube m_cube;
	Grid m_grid;
	CameraEditor m_camera;

};

