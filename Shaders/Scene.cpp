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
	m_gameObjects.push_back(obj);
	m_gameObjects.back()->Create();
	m_gameObjects.back()->SetIsSelected(false);
}

std::vector<GameObject*>& Scene::GetGameObjects()
{
	return m_gameObjects;
}

