#pragma once

#include "GameObject.h"

class Grid : public GameObject
{
public:

	Grid(GLuint size = 10, GLfloat lineWidh = 1.0f, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f);

public:

	virtual void Create();
	virtual void Render();

private:

	GLuint m_size;
	GLuint m_totalVertices;

	GLfloat m_lineWidth;

	glm::vec3 m_color;
};

