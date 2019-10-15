#include "glad/glad.h"
#include <iostream>
#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Debug.h"
#include "Input.h"
#include "Screen.h"
#include "Interface.h"

#include "Cube.h"
#include "Camera.h"

GLfloat time = 0;
bool IsGameEngineRunning = true;

int main(int argc, char* args[])
{

	// -------------------------------------------#  Initilize the Screen

	Screen::Instance()->Initialize(1280, 720, 4, 6, true);

	// -------------------------------------------#  Create Shader Program and shader
	
	Cube m_cube;
	Camera m_camera;

	m_camera.LookAt();
	m_camera.Projection();

	// -------------------------------------------# VBO Set up


	// get id of shader program for use belw (temp)
	GLint shaderProgram = Shader::GetShaderProgram();

	// Get uniform id
	GLint modelID = glGetUniformLocation(shaderProgram, "model");
	GLint viewID = glGetUniformLocation(shaderProgram, "view");
	GLint projID = glGetUniformLocation(shaderProgram, "proj");

	//
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f);

	// Enable Depth for 3d so quads don't overlap.
	glEnable(GL_DEPTH_TEST);

	// Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// -------------------------------------------#  Main loop
	while (IsGameEngineRunning)
	{
		// -------------------------------------------# 

		// Clears the buffers
		Screen::Instance()->ClearBuffers();

		// Updates the poll events
		Input::Instance()->PollEvents();

		// Start the Dear ImGui frame
		Screen::Instance()->ImGuiFrame();

		// Draws all the GUI and UI
		Interface::Instance()->DrawUi();

		// Get key states
		KeyState keyStates = Input::Instance()->GetKeyStates();

		// -------------------------------------------# Code

		//if (Input.KeyDown("W"));

		if (keyStates[SDL_SCANCODE_W])
		{
			position.z += 0.01f;
		}

		if (keyStates[SDL_SCANCODE_S])
		{
			position.z -= 0.01f;
		}

		if (keyStates[SDL_SCANCODE_Q])
		{
			position.y += 0.01f;
		}

		if (keyStates[SDL_SCANCODE_E])
		{
			position.y -= 0.01f;
		}

		model = glm::translate(glm::mat4(1.0f), position);

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &m_camera.GetLookAt()[0][0]);
		glUniformMatrix4fv(projID, 1, GL_FALSE, &m_camera.GetProjection()[0][0]);
	
		m_cube.Render();


		// -------------------------------------------#

		Debug::GLErrors();

		// -------------------------------------------#

		// Render ImGui Windows
		Screen::Instance()->ImGuiRender();

		// Swap
		Screen::Instance()->SwapBuffers();
	}

	// -------------------------------------------# Shut Down

	Screen::Instance()->ShutDown();

	system("pause");
	return 0;
}