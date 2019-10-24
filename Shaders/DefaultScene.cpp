#include "DefaultScene.h"
#include "SceneManager.h"
#include <iostream>

DefaultScene::DefaultScene()
{
	SceneManager::Instance()->PushScene("DefaultScene", this);

	// TODO MAKE A FUNCTION TO PASS THEM IN A ARRAY *
	m_gameObjects.push_back(m_cube);
	m_gameObjects.push_back(m_grid);
	m_gameObjects.push_back(m_camera);
	
	// -------------------------------------------#  Create Game Objects

	/*for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i].Create();
	}*/

	m_quad.Create();
	//m_cube.Create();
	m_grid.Create();

	// -------------------------------------------#  Create Camera Perspective

	m_camera.SetPerspectiveView();
}

void DefaultScene::Update()
{
	// -------------------------------------------# Update Game Objects

	m_camera.Update();

}

void DefaultScene::Render()
{
	// -------------------------------------------# Render Game Objects

	m_quad.Render();
	m_grid.Render();
	//m_cube.Render();
	
}
