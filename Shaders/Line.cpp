#include "Line.h"
#include "Debug.h"

// IN PROGRESS NOT FINISHED

Line::Line()
{
	m_isLit = false;
	m_isTextured = false;

	m_color = nullptr;
	m_vertex = nullptr;
}

void Line::Create()
{

	//if (m_vertex == nullptr)
	//{
	//	Debug::WarningLog("Vertex data in Line, it's null.");
	//} 
	//else if (m_color == nullptr)
	//{
	//	Debug::WarningLog("Color data in Line, it's null.");
	//}
	//else
	{
		GLfloat line[] = {  0.0f, 0.0f, 0.0f,
							0.0f, 5.0f, 0.0f };

		GLfloat color[] = { 1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f };

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
		m_material.BufferData(color, sizeof(color), "colorIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.UnbindBuffer();

		m_material.UnbindVertexArray();

		m_material.BindUniform("model");
		m_material.BindUniform("isLit");
		m_material.BindUniform("isTextured");
	}
}

void Line::Update()
{
}

void Line::Render()
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

void Line::SetVertex(GLfloat* vertex)
{
	m_vertex = vertex;
}

void Line::SetColor(GLfloat* color)
{
	m_color = color;
}

void Line::SetColor(glm::vec3 color)
{
	GLfloat tempcolor[] = { color.x, color.y, color.z,
							color.x, color.y, color.z };

	m_color = tempcolor;
}
