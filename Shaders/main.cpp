#include "glad/glad.h"
#include <iostream>
#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Debug.h"
#include "Input.h"
#include "Screen.h"
#include "Interface.h"
#include "Shader.h"


GLfloat time = 0;
bool IsGameEngineRunning = true;

int main(int argc, char* args[])
{
	// -------------------------------------------#  Initilize the Screen

	Screen::Instance()->Initialize(1280, 720, 4, 6, true);

	// -------------------------------------------#  Create Shader Program and shader

	Shader::Instance()->CreateShaderProgram();
	Shader::Instance()->CreateShader("Main.vert", "Main.frag");

	// -------------------------------------------# VBO Set up

	GLfloat vertices[] = {

			-0.5f, 0.5f, 0.0f,
			 0.5f, 0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			
	};

	GLfloat vertices3d[] = { -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
							  0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f
	};


	GLfloat colors3d[] = { 1.0f ,0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
						   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
						   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
						   0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
						   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
						   1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
						   1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
						   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
						   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	//inex values for our EBO
	GLuint indices3d[] = { 0,  1,  3,  3,  1,  2,
						   4,  5,  7,  7,  5,  6,
						   8,  9,  11, 11, 9,  10,
						   12, 13, 15, 15, 13, 14,
						   16, 17, 19, 19, 17, 18,
						   20, 21, 23, 23, 21, 22
	};

	GLfloat vertices2[] = {

			-100,  100, 
			 100,  100, 
			-100, -100,
			 100, -100, 

	};

	GLfloat colorData[] = {

			 1.0f, 0.0f, 0.0f,
			 0.0f, 0.0f, 1.0f,
			 0.0f, 1.0f, 1.0f,
			 0.0f, 1.0f, 0.0f,
	};

	GLuint indices[] = { 

			0, 1, 3,
			3, 1, 2
	};

	// get id of shader program for use belw (temp)
	GLint shaderProgram = Shader::Instance()->GetShaderProgram();

	// Get uniform id
	GLint timeID = glGetUniformLocation(shaderProgram, "time");
	GLint modelID = glGetUniformLocation(shaderProgram, "model");
	GLint viewID = glGetUniformLocation(shaderProgram, "view");
	GLint projID = glGetUniformLocation(shaderProgram, "proj");

	// get ids of shader variables so we can use them
	GLint vertex = glGetAttribLocation(shaderProgram, "vertexIn");
	GLint color = glGetAttribLocation(shaderProgram, "colorIn");

	
	if (vertex == -1)
	{
		Debug::ErrorLog("Vertex");
	}

	if (color == -1)
	{
		Debug::ErrorLog("Color");
	}
	
	// switches on the shader variables so we can get them

	// create VBO
	GLuint colorVBO = 0;
	GLuint vertexVBO = 0;
	GLuint EBO = 0;
	GLuint VAO = 0;

	// 
	glm::vec3 camPos = glm::vec3(0.0f);
	const glm::vec3 TARGET = glm::vec3(0.0f, 0.0, -1.0f);

	//
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	// generates 
	glGenVertexArrays(1, &VAO);

	// bind 
	glBindVertexArray(VAO);
	{
		// generates space in the vram/memory
		glGenBuffers(1, &colorVBO);
		glGenBuffers(1, &vertexVBO);

		//// bind, fill and link vertex buffer so we can use it
		//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		//glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(vertex);

		// bind, fill and link vertex buffer so we can use it
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3d), vertices3d, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex);

		//// bind, fill and link vertex buffer so we can use it
		//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
		//glVertexAttribPointer(vertex, 2, GL_INT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(vertex);

		////bind, fill and link frag buffer so we can use it
		//glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_DYNAMIC_DRAW);
		//glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(color);

		// bind, fill and link frag buffer so we can use it
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors3d), colors3d, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(color);

		// bind, fill and link frag buffer so we can use it
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3d), indices3d, GL_DYNAMIC_DRAW);
	}

	// unbind
	//glBindVertexArray(0);

	camPos.z += 2.0f;

	// create view matrix
	view = glm::lookAt(camPos, 
					   camPos + TARGET,  
					   glm::vec3(0.0f, 1.0f, 0.0f));
	
	// set the projection to a 3d perspective view
	int width = Screen::Instance()->GetScreenWidth();
	int height = Screen::Instance()->GetScreenHeight();

	const float FOV = 45.0f;
	const float ASPECT_RATIO = (float)width / (float)height;
	const float NEAR_CLIP = 0.1f;
	const float FAR_CLIP = 100.0f;

	proj = glm::perspective(FOV, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP);

	glEnable(GL_DEPTH_TEST);

	// Ortographic view

	//proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

	glm::vec3 position = glm::vec3(0.0f);

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


		KeyState keyStates = Input::Instance()->GetKeyStates();

		// -------------------------------------------# Code

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
		glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
	
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		// Pass datea
	//	glUniform1f(timeID, time);

		// pass matrix

		
		


		
		//glBindVertexArray(VAO);


		//glBindVertexArray(0);

		//Debug::Instance()->Log(time);

		time += SDL_GetTicks() / 1000.0f;

		// -------------------------------------------#

		Debug::GLErrors();

		// -------------------------------------------#

		// Render ImGui Windows
		Screen::Instance()->ImGuiRender();

		// Swap
		Screen::Instance()->SwapBuffers();
	}

	// -------------------------------------------# Shut Down

	

	glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(color);

	Screen::Instance()->ShutDown();

	system("pause");
	return 0;
}