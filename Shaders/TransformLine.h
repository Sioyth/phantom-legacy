#pragma once
#include <glm.hpp>

#include "Material.h"
#include "Transform.h"
#include "AABB.h"

class TransformLine
{
public :

	TransformLine(glm::vec3 translation);

	void Create(glm::vec3 point1, glm::vec3 point2, glm::vec3 color);
	void Update();
	void Render();

public:

	void SetVertex(GLfloat* vertex);

	void SetColor(GLfloat* color);
	void SetColor(glm::vec3 color);
	void SetColor(glm::vec3 color1, glm::vec3 color2);

	AABB GetCollider() { return m_collider; };

private:

	bool m_isLit;
	bool m_isTextured;

	GLfloat* m_color;
	GLfloat* m_vertex;

	AABB m_collider;
	Material m_material;
	Transform m_transform;
	
};

