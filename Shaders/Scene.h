#pragma once
#include <vector>

#include "GameObject.h"

class Scene
{
public:

	void Pause();
	void Resume();

	void Editing();

	virtual void Update() = 0;
	virtual void Render() = 0;

	void PushGameObject(GameObject* obj);
	std::vector<GameObject*>& GetGameObjects();

protected:

	bool m_isEditing;
	bool m_isRunning;
	std::vector<GameObject*> m_gameObjects;
};

