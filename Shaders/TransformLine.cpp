#include "TransformLine.h"
#include "Debug.h";

TransformLine::TransformLine()
{
	m_isLit = false;
	m_isTextured = false;

	m_color = nullptr;
	m_vertex = nullptr;
}

void TransformLine::Create(glm::vec3 point1, glm::vec3 point2, glm::vec3 color, glm::vec3 translation)
{
	//Collider

	m_transform.Translate(translation);
	m_collider.SetPosition(m_transform.GetPosition());
	m_collider.CalculateMinMax();

	//Material

	GLfloat line[] = { point1.x, point1.y, point1.z,
					   point2.x, point2.y, point2.z };

	GLfloat colorLine[] = { color.x, color.y, color.z,
						color.x, color.y, color.z };


	m_material.CreateVertexArray();
	m_material.BindVertexArray();

	m_material.CreateBuffer("vertexVBO");
	m_material.BindBuffer("vertexVBO");
	m_material.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_material.BufferData(line, sizeof(line), "vertexIn", GL_DYNAMIC_DRAW);
	m_material.UnbindBuffer();

	m_material.CreateBuffer("colorVBO");
	m_material.BindBuffer("colorVBO");
	m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_material.BufferData(colorLine, sizeof(colorLine), "colorIn", GL_DYNAMIC_DRAW);
	m_material.UnbindBuffer();

	m_material.UnbindBuffer();

	m_material.UnbindVertexArray();

	m_material.BindUniform("model");
	m_material.BindUniform("isLit");
	m_material.BindUniform("isTextured");
	
}

void TransformLine::Update(glm::vec3 bound)
{
	m_collider.SetPosition(bound);
	m_collider.CalculateMinMax();
}

void TransformLine::Render()
{
	{
		// Send Uniforms Data
		m_material.SendUniformData("isLit", m_isLit);
		m_material.SendUniformData("isTextured", m_isTextured);
		m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());

		//glLineWidth(5.0f);

		// Render Line
		m_material.BindVertexArray();
		m_material.DrawVertexArray(GL_LINES, 0, 2);
		m_material.UnbindVertexArray();
	}
}

void TransformLine::SetVertex(GLfloat* vertex)
{
	m_vertex = vertex;
}

void TransformLine::SetColor(GLfloat* color)
{
	m_color = color;
}

void TransformLine::Translate(glm::vec3 translation)
{
	m_transform.Translate(translation);
}

void TransformLine::SetColliderDimension(glm::vec3 dimension)
{
	m_collider.SetDimension(dimension);
}
