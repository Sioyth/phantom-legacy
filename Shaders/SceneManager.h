#pragma once
#include <map>
#include <string>

#include "Scene.h"

class SceneManager
{
public:

	static SceneManager* Instance();

public:

	void ChangeScene(Scene* scene);
	void ChangeScene(std::string name);

	void PushScene(std::string name, Scene* scene);

	Scene& GetCurrentScene();

private:

	Scene* m_currentScene = nullptr;
	std::map<std::string, Scene* > m_scenes;

private:

	SceneManager() {};
	SceneManager(const SceneManager&);
	SceneManager operator=(const SceneManager);
};

