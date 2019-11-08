#include "PointLight.h"

PointLight::PointLight()
{
	m_isTextured = false;
	m_isLit = false;
	m_color.r = 1.0f;
	m_color.g = 0.0f;
	m_color.b = 0.0f;

	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

void PointLight::Create()
{
	GLfloat vertices[]{ 0.0f,  0.0f, 0.0f };

	GLfloat colors[]{ m_color.r, m_color.g, m_color.b };

	m_shader.CreateVertexArray();
	m_shader.BindVertexArray();
	{
		m_shader.CreateBuffer("vertexVBO");
		m_shader.BindBuffer("vertexVBO");
		m_shader.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_shader.BufferData(vertices, sizeof(vertices), "vertexIn", GL_DYNAMIC_DRAW);
		m_shader.UnbindBuffer();

		m_shader.CreateBuffer("colorVBO");
		m_shader.BindBuffer("colorVBO");
		m_shader.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_shader.BufferData(colors, sizeof(colors), "colorIn", GL_DYNAMIC_DRAW);
		m_shader.UnbindBuffer();

	}
	m_shader.UnbindVertexArray();

	// Uniforms
	m_shader.BindUniform("model");
	m_shader.BindUniform("lightColor");
	m_shader.BindUniform("isTextured");

	m_shader.BindUniform("isLit");
	m_shader.BindUniform("light.position");
	m_shader.BindUniform("light.ambient");
	m_shader.BindUniform("light.diffuse");
	m_shader.BindUniform("light.specular");


}

void PointLight::Render()
{
	m_shader.SendUniformData("isTextured", m_isTextured);
	m_shader.SendUniformData("isLit", m_isLit);
	m_shader.SendUniformData("lightColor", m_color);

	m_shader.SendUniformData("light.position", m_transform.GetPosition());
	m_shader.SendUniformData("light.ambient",m_ambient);
	m_shader.SendUniformData("light.diffuse", m_diffuse);
	m_shader.SendUniformData("light.specular",m_specular);

	m_shader.BindVertexArray();
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	glPointSize(30.0f); // TODO put this in shader class
	glDrawArrays(GL_POINTS, 0, 1); // TODO put this in shader class.
	m_shader.DrawVertexArray(GL_POINTS, 0, 1);
}
