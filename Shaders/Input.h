#pragma once
#include <glm.hpp>
#include <string>
#include <SDL.h>
#include <map>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"

#define PHANTOM_A SDL_SCANCODE_A
#define PHANTOM_B SDL_SCANCODE_B
#define PHANTOM_C SDL_SCANCODE_C
#define PHANTOM_D SDL_SCANCODE_D
#define PHANTOM_E SDL_SCANCODE_E
#define PHANTOM_F SDL_SCANCODE_F
#define PHANTOM_G SDL_SCANCODE_G
#define PHANTOM_H SDL_SCANCODE_H
#define PHANTOM_I SDL_SCANCODE_I
#define PHANTOM_J SDL_SCANCODE_J
#define PHANTOM_K SDL_SCANCODE_K
#define PHANTOM_L SDL_SCANCODE_L
#define PHANTOM_M SDL_SCANCODE_M
#define PHANTOM_N SDL_SCANCODE_N
#define PHANTOM_O SDL_SCANCODE_O
#define PHANTOM_P SDL_SCANCODE_P
#define PHANTOM_Q SDL_SCANCODE_Q
#define PHANTOM_R SDL_SCANCODE_R
#define PHANTOM_S SDL_SCANCODE_S
#define PHANTOM_T SDL_SCANCODE_T
#define PHANTOM_U SDL_SCANCODE_U
#define PHANTOM_V SDL_SCANCODE_V
#define PHANTOM_W SDL_SCANCODE_W
#define PHANTOM_X SDL_SCANCODE_X
#define PHANTOM_Y SDL_SCANCODE_Y
#define PHANTOM_Z SDL_SCANCODE_Z

#define PHANTOM_1 SDL_SCANCODE_1
#define PHANTOM_2 SDL_SCANCODE_2
#define PHANTOM_3 SDL_SCANCODE_3
#define PHANTOM_4 SDL_SCANCODE_4
#define PHANTOM_5 SDL_SCANCODE_5
#define PHANTOM_6 SDL_SCANCODE_6
#define PHANTOM_7 SDL_SCANCODE_7
#define PHANTOM_8 SDL_SCANCODE_8
#define PHANTOM_9 SDL_SCANCODE_9
#define PHANTOM_0 SDL_SCANCODE_0

#define PHANTOM_RETURN	     SDL_SCANCODE_RETURN 
#define PHANTOM_BACKSPACE    SDL_SCANCODE_BACKSPACE 
#define PHANTOM_TAB          SDL_SCANCODE_TAB 
#define PHANTOM_SPACE        SDL_SCANCODE_SPACE 
#define PHANTOM_MINUS        SDL_SCANCODE_MINUS 
#define PHANTOM_EQUALS       SDL_SCANCODE_EQUALS 
#define PHANTOM_LEFTBRACKET  SDL_SCANCODE_LEFTBRACKET 
#define PHANTOM_RIGHTBRACKET SDL_SCANCODE_RIGHTBRACKET 
#define PHANTOM_BACKSLASH    SDL_SCANCODE_BACKSLASH 

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

public:

	bool KeyDown(std::string key);

private:

	Input() {};
	Input(const Input&);
	Input operator=(const Input);

private:

	bool m_IsKeyPressed;

	KeyState m_keyStates;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mousePosition;

	std::map<std::string, int> m_keys;

};

