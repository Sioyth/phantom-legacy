#include "SceneManager.h"
#include "Debug.h"

SceneManager* SceneManager::Instance()
{
	static SceneManager* sceneManager = new SceneManager;
	return sceneManager;
}

void SceneManager::ChangeScene(Scene* scene)
{
	m_currentScene = scene;
}

void SceneManager::ChangeScene(std::string name)
{
	if (m_scenes.find(name) != m_scenes.end())
	{
		m_currentScene = m_scenes[name];
		m_currentScene->Start();
	}
	else
	{
		Debug::ErrorLog("Scene " + name + " couldn't be finded!");
	}
}

void SceneManager::PushScene(std::string name, Scene* scene)
{
	if (scene)
	{
		m_scenes[name] = scene;
	}
	else
	{
		Debug::ErrorLog("Scene " + name + " couldn't be pushed!");
	}
}

Scene& SceneManager::GetCurrentScene()
{
	if (m_currentScene != nullptr)
	{
		return *m_currentScene;
	}
	else 
	{
		//return;
	}
}
