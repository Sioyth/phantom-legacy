#include "Primitives.h"

void Primitives::SetColor(glm::vec3 color)
{
	m_color = color;
}

void Primitives::SetColor(float r, float g, float b)
{
	m_color = glm::vec3(r, g, b);
}
