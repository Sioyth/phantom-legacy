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
	bool PickObject(Ray& ray, RayCastHit& hit);

	void PickMove(Ray& ray);
	void PickRelease();

	void PushGameObject(GameObject* obj);
	std::vector<GameObject*>& GetGameObjects();

	void SetSelectedObject(GameObject* selected);
	GameObject* GetSelectedGameObject();


	inline float GetMass() { return m_mass; }
	inline float GetForceMultiplyer() { return m_fMultiplyer; }
	inline float GetVelocityMultiplyer() { return m_vMultiplyer; }

	inline void SetMass(float m) { m_mass = m; }
	inline void SetForceMultiplyer(float f) { m_fMultiplyer = f; }
	inline void SetVelocityMultiplyer(float v) { m_vMultiplyer = v; }

protected:

	bool m_isEditing;
	bool m_isRunning;
	bool m_isGridActive;
	bool m_isPlaneActive;
	
	float m_mass = 1.0f;
	float m_fMultiplyer = 500.0f;
	float m_vMultiplyer = 15.0f;

	GameObject* m_selectedObject;
	std::vector<GameObject*> m_gameObjects;

	static int s_currentSelectedGameObject;
};

