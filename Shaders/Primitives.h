#pragma once
#include "GameObject.h"

class Primitives : public GameObject
{

public:

	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Create() = 0;

	void SetColor(glm::vec3 color);
	void SetColor(float r, float g, float b);

protected:

	glm::vec3 m_color;
};

