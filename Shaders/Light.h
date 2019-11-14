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

	GLfloat m_attenuationQuad;
	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;

	glm::vec3 m_color;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

