#pragma once
#include "GameObject.h"

class Light : public GameObject
{
public:

	Light() {};

	virtual void Create() {};
	virtual void Render() {};
	virtual void Update() {};

public:

	void SetLightPower(GLfloat power);
	void SetLightColor(glm::vec3 color);

protected:

	GLfloat m_power;
	GLfloat m_intensity;

	glm::vec3 m_color;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

