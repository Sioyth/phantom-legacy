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

#define PVD_HOST "127.0.0.1"

class Screen
{
public:

	static Screen* Instance();

public:

	void Initialize(int widht, int height, int major, int minor, bool mode);
	void ShutDown();

	void PhysX();

	void ImGuiFrame();
	void ImGuiRender();

	void ClearBuffers();
	void SwapBuffers();

	void DisplayGraphicsInfo();
	void DisplayExtensionsInfo();

	int GetScreenWidth();
	int GetScreenHeight();

public:

	const physx::PxPhysics* GetPxPhysics();

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

	physx::PxDefaultAllocator m_allocator;
	physx::PxDefaultErrorCallback m_errorCallback;

	physx::PxPhysics* m_physics;
	physx::PxFoundation* m_foundation;
	physx::PxDefaultCpuDispatcher* m_dispatcher;

	physx::PxScene* m_scene;


	physx::PxPvd* m_pvd; // Physx Visual debuger

private:

	int m_widht;
	int m_height;

	bool m_depthTest;

	glm::vec4 m_backgroundColor;
};

