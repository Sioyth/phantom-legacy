#include "DefaultScene.h"
#include "SceneManager.h"
#include <iostream>

DefaultScene::DefaultScene()
{
	SceneManager::Instance()->PushScene("DefaultScene", this);

	// Create Default Shader
	Shader::CreateShader("Main.vert", "Main.frag");

	// TODO MAKE A FUNCTION TO PASS THEM IN A ARRAY *
	/*m_gameObjects.push_back(m_cube);
	m_gameObjects.push_back(m_grid);*/
	
	// -------------------------------------------#  Create Game Objects

	/*for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i].Create();
	}*/

	m_pointLight = new PointLight;

	m_camera.Create();

	m_quad.Create();
	//m_quad.LoadTexture("Textures/Water_2.jpg", "Water");

	m_cube.Create();
	m_grid.Create();
	m_skyBox.Create();

	m_quad.Scale(glm::vec3(50.0f));
	m_quad.Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	m_pointLight->Create();
	m_pointLight->Translate(0.0f, 3.0f, 0.0f);

	m_gameObjects.push_back(m_pointLight);
	
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

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		(*m_gameObjects[i]).Render();
	}

	m_quad.Render();
	//m_grid.Render();
	m_cube.Render();
	//m_skyBox.Render();
	m_pointLight->Render();
}
