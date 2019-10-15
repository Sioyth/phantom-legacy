#include "Input.h"

Input* Input::Instance()
{
	static Input* input = new Input;
	return input;
}

KeyState Input::GetKeyStates()
{
	return m_keyStates;
}

glm::vec2 Input::GetMouseMotion()
{
	return m_mouseMotion;
	
}

glm::vec2 Input::GetMousePosition()
{
	return m_mousePosition;
}

bool Input::KeyDown(std::string key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Input::PollEvents()
{
	SDL_Event events;

	// -------------------------------------------# Updates Key States

	m_keyStates = SDL_GetKeyboardState(nullptr);

	// -------------------------------------------# Reset Mouse Motion

	m_mouseMotion.x = 0;
	m_mouseMotion.y = 0;

	// -------------------------------------------# Polls Events

	while (SDL_PollEvent(&events))
	{
		//ImGui Events
		ImGui_ImplSDL2_ProcessEvent(&events);

		// Updates Mouse Position;
		m_mousePosition.x = events.motion.x;
		m_mousePosition.y = events.motion.y;

		switch (events.type)
		{
			case SDL_QUIT:
			{
				
				break;
			}

			case SDL_KEYDOWN:
			{
				m_IsKeyPressed = true;
				break;
			}

			case SDL_KEYUP:
			{
				m_IsKeyPressed = false;
				break;
			}

			case SDL_MOUSEMOTION:
			{
				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.x = events.motion.yrel;

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{

						break;
					}

					case SDL_BUTTON_RIGHT:
					{

						break;
					}

					case SDL_BUTTON_MIDDLE:
					{

						break;
					}

				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{

						break;
					}

					case SDL_BUTTON_RIGHT:
					{

						break;
					}

					case SDL_BUTTON_MIDDLE:
					{

						break;
					}

				}
				break;
			}
		}
	}
}
