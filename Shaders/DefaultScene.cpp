#include "DefaultScene.h"
#include "SceneManager.h"
#include <iostream>

#include "Cube.h"

Cube* m_cube[10];

DefaultScene::DefaultScene()
{

	m_isGridActive = false;
	m_isPlaneActive = true;

	SceneManager::Instance()->PushScene("DefaultScene", this);

	// Create Default Shader
	Shader::CreateShader("Main.vert", "Main.frag", "Main");
	Shader::CreateShader("Noise.vert", "Noise.frag", "Noise");

	Shader::UseShaderProgram("Main");

	Light* light = new Light(PointLight);
	light->Create();
	light->Translate(0.0f, 15.0f, 0.0f);
	//light->SetLightColor(glm::vec3(0.8f, 0.6f, 0.0f));

	m_gameObjects.push_back(light);

	m_camera.Create();

	m_debugPlane.Create();
	m_debugPlane.Scale(glm::vec3(50.0f));
	m_debugPlane.Rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	m_grid.Create();
	m_skyBox.Create();

	float j = 0;
	float l = 0;
	for (int k = 0; k < 1; k++)
	{

		for (int i = 0; i < 10; i++)
		{
			j = j + 1.0f;
			m_cube[i] = new Cube;
			m_cube[i]->SetPosition(glm::vec3(l, j, 0.0f));
			if (i == 9)
				m_cube[i]->SetPosition(glm::vec3(0.0f, 30, 0.0f));
			m_cube[i]->Create();
			m_gameObjects.push_back(m_cube[i]);

		}


		l += 1.0f;
	}
	

	// -------------------------------------------#  Create Camera Perspective

	m_camera.SetPerspectiveView();
}

void DefaultScene::Update()
{
	// -------------------------------------------# Update Game Objects
	m_camera.Update();

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		(*m_gameObjects[i]).Update();
	}
}

void DefaultScene::Render()
{
	// -------------------------------------------# Render Game Objects

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		(*m_gameObjects[i]).Render();
	}

	if (m_isPlaneActive)
	{
		m_debugPlane.Render();
	}
	
	if (m_isGridActive)
	{
		m_grid.Render();
	}

	//m_skyBox.Render();
}
