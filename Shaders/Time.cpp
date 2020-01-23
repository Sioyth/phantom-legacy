#include "Time.h"
#include "Time.h"

#include <SDL.h>

float Time::m_deltaTime;
float Time::m_elapsedTime;

void Time::Update()
{
	m_elapsedTime = SDL_GetTicks();
	m_deltaTime = m_elapsedTime / 1000.0f;
}

float Time::GetDeltaTime()
{
	return m_deltaTime;
}

float Time::GetElapsedTime()
{
	return m_elapsedTime;
}
