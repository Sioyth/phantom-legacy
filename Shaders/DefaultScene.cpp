#include "DefaultScene.h"
#include "SceneManager.h"
#include <iostream>
#include <time.h>

#include "Cube.h"
#include "Debug.h"
#include "Ball.h"

#include <gtc/random.hpp>

Cube* m_cube[10];

//-----------------------------------------------------------------------------
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

	srand(time(0));

	glm::vec3 color;
	color.x = glm::linearRand(0.0f, 1.0f);
	color.y = glm::linearRand(0.0f, 1.0f);
	color.z = glm::linearRand(0.0f, 1.0f); 

	glm::vec3 color1(color);

	color.x = glm::linearRand(0.0f, 1.0f);
	color.y = glm::linearRand(0.0f, 1.0f);
	color.z = glm::linearRand(0.0f, 1.0f);
	glm::vec3 color2(color);

	float xPos = 0;
	float yPos = 0;
	float zPos = 0;

	int size = 5;

	for (int z = 0; z < size; z++)
	{
		xPos = 0;
		for (int k = 0; k < size; k++)
		{

			//glm::vec3 tempColor = color1;

			yPos = 0.5f;
			for (int i = 0; i < size; i++)
			{

				//glm::vec3 tempColor = color1 + k/ 20.0f * (color2 - color1);
				glm::vec3 tempColor = color1 + (k + i + z) / (float)size * (color2 - color1);
				//glm::vec3 tempColor = color1 + sqrt((k - size/2 + 0.5f) * (k - size / 2 + 0.5f) + (i - size / 2 + 0.5f) * (i - size / 2 + 0.5f)) / size * (color2 - color1);

				
				m_cube[i] = new Cube;
				m_cube[i]->SetPosition(glm::vec3(xPos, yPos, zPos));
				/*if (i == 9)
					m_cube[i]->SetPosition(glm::vec3(0.0f, 30, 0.0f));*/
				m_cube[i]->Create();


				/*Debug::Log(glm::ballRand(1.0f));

				glm::vec3 color;
				color.x = glm::linearRand(0.0f, 1.0f);
				color.y = glm::linearRand(0.0f, 1.0f);
				color.z = glm::linearRand(0.0f, 1.0f);*/

				m_cube[i]->SetColor(tempColor);
				m_gameObjects.push_back(m_cube[i]);

				yPos ++;
			}


			xPos ++;
		}

		zPos ++;
	}
	

	// -------------------------------------------#  Create Camera Perspective

	m_camera.SetPerspectiveView();
}
bool spaceDown = false;
//-----------------------------------------------------------------------------
void DefaultScene::Update()
{
	Debug::Log(spaceDown);
	if (Input::Instance()->KeyDown(Keycode::SPACE))
	{
		if (!spaceDown)
		{
			spaceDown = true;
			this->PushGameObject(new Ball(m_camera, m_mass, m_vMultiplyer, m_fMultiplyer));
		}
	}
	else
	{
		spaceDown = false;
	}

	// -------------------------------------------# Update Game Objects
	m_camera.Update();

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		(*m_gameObjects[i]).Update();
		(*m_gameObjects[i]).Render();
	}
}

//-----------------------------------------------------------------------------
void DefaultScene::Render()
{
	// -------------------------------------------# Render Game Objects

	/*for (int i = 0; i < m_gameObjects.size(); i++)
	{
		
	}*/

	if (m_isPlaneActive)
	{
		m_debugPlane.Render();
	}
	
	if (m_isGridActive)
	{
		m_grid.Render();
	}

}
