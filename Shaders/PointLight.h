#pragma once
#include "Light.h"
#include "SphereCollider.h"

class PointLight : public Light
{
public:

	PointLight();

	void Create();
	void Render();
	void Update() {};

public:

	const SphereCollider& GetSphereCollider();

private:

	SphereCollider m_sphereCollider;
};

