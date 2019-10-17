#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:

	Cube();

	virtual void Render();
	virtual void Create();
};

