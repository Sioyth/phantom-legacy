#include "Scene.h"

void Scene::Pause()
{
	m_isRunning = false;
}

void Scene::Resume()
{
	m_isRunning = true;
}
