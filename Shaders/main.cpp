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

	// -------------------------------------------#  FBO

	GLuint fbo;

	glGenFramebuffers(1, &fbo);

	// -------------------------------------------#  Texture

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach to fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);



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

		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		Screen::Instance()->ClearBuffers();

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		{

		}
		else
		{
			Debug::ErrorLog("FBO not complete!");
		}

		glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &m_camera.GetLookAt()[0][0]);
		glUniformMatrix4fv(projID, 1, GL_FALSE, &m_camera.GetProjection()[0][0]);

	

		m_cube.Render();

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		// attach to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		ImGui::Begin("Scene Window");

		//get the mouse position
		ImVec2 pos = ImGui::GetCursorScreenPos();

		//pass the texture of the FBO
		//window.getRenderTexture() is the texture of the FBO
		//the next parameter is the upper left corner for the uvs to be applied at
		//the third parameter is the lower right corner
		//the last two parameters are the UVs
		//they have to be flipped (normally they would be (0,0);(1,1) 
		ImGui::GetWindowDrawList()->AddImage(
			(void*)texture,
			ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(ImGui::GetCursorScreenPos().x + Screen::Instance()->GetScreenWidth() / 2,
				ImGui::GetCursorScreenPos().y + Screen::Instance()->GetScreenHeight() / 2), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();


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