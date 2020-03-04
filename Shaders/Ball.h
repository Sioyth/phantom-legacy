#pragma once
#include "Primitives.h"
#include "SphereCollider.h"

#include "CameraEditor.h"

class Ball : public Primitives
{
public:

	Ball(CameraEditor& camera, float mass, float vMultiplyer, float fMultiplyer);

	virtual void Render();
	virtual void Create();
	virtual void Update();

private:

	float m_mass;
	float m_vMultiplyer;
	float m_fMultiplyer;

	CameraEditor* m_camera;
	SphereCollider* m_sphereCollider;
};

