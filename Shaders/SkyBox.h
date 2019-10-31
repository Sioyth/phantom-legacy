#pragma once
#include "GameObject.h"

class SkyBox : public GameObject
{
public:

	SkyBox();

	virtual void Render();
	virtual void Create();

};

