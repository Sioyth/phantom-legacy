#pragma once
#include <glm.hpp>
#include <SDL.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"

typedef const Uint8* KeyState; 

class Input
{
public:

	static Input* Instance();

public:

	void PollEvents();

public:

	KeyState GetKeyStates();

	glm::vec2 GetMouseMotion();
	glm::vec2 GetMousePosition();

private:

	Input() {};
	Input(const Input&);
	Input operator=(const Input);

private:

	bool m_IsKeyPressed;

	KeyState m_keyStates;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mousePosition;

};

