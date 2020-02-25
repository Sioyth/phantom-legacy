#pragma once
#include "GameObject.h"

class RayCastHit
{
public:

	GameObject* GetGameObject();
	void SetGameObject(GameObject* obj);

private:

		GameObject* m_gameObject;
};

