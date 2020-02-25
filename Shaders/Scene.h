#pragma once
#include <vector>

#include "GameObject.h"
#include "Physics.h"

class Scene
{
public:

	void Pause();
	void Resume();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void SetGrid(bool flag);
	void SetPlane(bool flag);
	
	bool GetGrid();
	bool GetPlane();

	void CreateScene();

	bool Raycast(Ray& ray, RayCastHit& hit, float maxDistance);

	void PushGameObject(GameObject* obj);
	std::vector<GameObject*>& GetGameObjects();

	void SetSelectedObject(GameObject* selected);
	GameObject* GetSelectedGameObject();

protected:

	bool m_isEditing;
	bool m_isRunning;
	bool m_isGridActive;
	bool m_isPlaneActive;

	GameObject* m_selectedObject;
	std::vector<GameObject*> m_gameObjects;

	static int s_currentSelectedGameObject;
};

