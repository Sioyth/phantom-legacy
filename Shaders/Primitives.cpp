#include "Primitives.h"

//-----------------------------------------------------------------------------
void Primitives::SetColor(glm::vec3 color)
{
	m_color = color;
	m_material.SetAmbient(color);
	m_material.SetDiffuse(color);
	m_material.SetSpecular(color);
}

//-----------------------------------------------------------------------------
void Primitives::SetColor(float r, float g, float b)
{
	m_color = glm::vec3(r, g, b);
}
