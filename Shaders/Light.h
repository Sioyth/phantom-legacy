#pragma once
#include "GameObject.h"

enum LightType
{
	PointLight = 1, DirectionalLight
};

class Light : public GameObject
{
public:

	Light(LightType type);

	void Create();
	void Render();
	void Update() {};

public:

	static GLuint GetTotalLights() { return s_totalLights; };

	void SetLightType(LightType type);
	void SetLightPower(GLfloat power);
	void SetLightColor(glm::vec3 color);

private:

	GLfloat m_power;
	GLfloat m_intensity;

	GLfloat m_attenuationQuad;
	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;

	GLuint m_lightNumber;

	glm::vec3 m_color;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	std::string m_lightNumberStr;

	LightType m_lightType;

private:

	static GLuint s_totalLights;

};

