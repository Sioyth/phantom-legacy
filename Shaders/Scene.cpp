#include "Scene.h"

void Scene::Pause()
{
	m_isRunning = false;
}

void Scene::Resume()
{
	m_isRunning = true;
}

void Scene::PushGameObject(GameObject* obj)
{
	m_gameObjects.push_back(*obj);
}
