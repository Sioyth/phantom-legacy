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

	void SetGrid(bool flag);
	void SetPlane(bool flag);
	
	bool GetGrid();
	bool GetPlane();

	void PushGameObject(GameObject* obj);
	std::vector<GameObject*>& GetGameObjects();

	static void SetSelectedObject(int objNr);
	static int GetSelectedGameObject();

protected:

	bool m_isEditing;
	bool m_isRunning;
	bool m_isGridActive;
	bool m_isPlaneActive;
	std::vector<GameObject*> m_gameObjects;

	static int s_currentSelectedGameObject;
};

