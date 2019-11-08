#pragma once
#include "Light.h"

class PointLight : public Light
{
public:

	PointLight();

	void Create();
	void Render();
	void Update() {};
};

