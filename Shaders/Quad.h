#pragma once
#include "Primitives.h"
#include "Texture.h"

class Quad : public Primitives
{
public:

	Quad();

	virtual void Render();
	virtual void Update() {};
	virtual void Create();

private:

	GLfloat m_metallic; // change
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};

