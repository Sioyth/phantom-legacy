#include "Scene.h"

int Scene::s_currentSelectedGameObject = -1;

void Scene::Pause()
{
	m_isRunning = false;
}

void Scene::Resume()
{
	m_isRunning = true;
}

void Scene::SetGrid(bool flag)
{
	m_isGridActive = flag;
}

void Scene::SetPlane(bool flag)
{
	m_isPlaneActive = flag;
}

bool Scene::GetGrid()
{
	return m_isGridActive;
}

bool Scene::GetPlane()
{
	return m_isPlaneActive;
}

void Scene::CreateScene()
{
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

void Scene::SetSelectedObject(int objNr)
{
	s_currentSelectedGameObject = objNr;
}

int Scene::GetSelectedGameObject()
{
	if (s_currentSelectedGameObject >= 0)
	{
		return s_currentSelectedGameObject;
	}
	else
	{
		return -1;
	}
}

