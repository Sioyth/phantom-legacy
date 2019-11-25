#pragma once
#include "Light.h"
#include "SphereCollider.h"
#include "AABB.h"

class PointLight : public Light
{
public:

	PointLight();

	void Create();
	void Render();
	void Update() {};

private:

	std::string m_lightNumberStr;
};

