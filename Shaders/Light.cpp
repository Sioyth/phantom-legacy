#include "Light.h"

void Light::SetLightColor(glm::vec3 color)
{
	m_color = color;
	m_ambient = color;
	m_diffuse = color;
	m_specular = color;
}
