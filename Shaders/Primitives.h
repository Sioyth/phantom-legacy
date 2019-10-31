#pragma once
#include "GameObject.h"

class Primitives : public GameObject
{

public:

	void SetColor(glm::vec3 color);
	void SetColor(float r, float g, float b);

protected:

	glm::vec3 m_color;
};

