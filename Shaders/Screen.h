#pragma once
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include "glad/glad.h"
#include <glm.hpp>

#include <PxPhysicsAPI.h>

class Screen
{
public:

	static Screen* Instance();

public:

	void Initialize(int widht, int height, int major, int minor, bool mode);
	void ShutDown();

	void ImGuiFrame();
	void ImGuiRender();

	void ClearBuffers();
	void SwapBuffers();

	void DisplayGraphicsInfo();
	void DisplayExtensionsInfo();

	int GetScreenWidth();
	int GetScreenHeight();

public:

	void SetDepthTest(bool flag);
	void SetBackgroundColor(glm::vec4 bgcolor);
	void SetBackgroundColor(float r, float g, float b, float a);

private:

	Screen() {};
	Screen(const Screen&);
	Screen& operator=(const Screen);

private:

	ImGuiIO io;
	SDL_Window* m_window;
	SDL_GLContext m_context;

private:

	int m_widht;
	int m_height;
	bool m_depthTest;

	glm::vec4 m_backgroundColor;
};

