#pragma once
#include <vector>

#include "GameObject.h"

class Scene
{
public:

	void Pause();
	void Resume();

	void Editing();

	virtual void Update() {};
	virtual void Render() {};

	void PushGameObject(GameObject* obj);

protected:

	bool m_isEditing;
	bool m_isRunning;
	std::vector<GameObject*> m_gameObjects;
};

