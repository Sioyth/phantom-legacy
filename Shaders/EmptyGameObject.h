#pragma once
#include "GameObject.h"

class EmptyGameObject : public GameObject
{
public:

	EmptyGameObject();

	virtual void Create();
	virtual void Render();
	virtual void Update() {};

private:

	
	
};

