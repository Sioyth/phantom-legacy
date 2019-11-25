#pragma once
#include "GameObject.h"

class Line : public GameObject
{
public:

	Line();

	virtual void Create();
	virtual void Update();
	virtual void Render();

public:

	void SetVertex(GLfloat* vertex);

	void SetColor(GLfloat* color);
	void SetColor(glm::vec3 color);
	void SetColor(glm::vec3 color1, glm::vec3 color2);

private:

	GLfloat* m_color;
	GLfloat* m_vertex;
};

