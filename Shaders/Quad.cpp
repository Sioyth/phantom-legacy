#include "Quad.h"

Quad::Quad()
{
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
	m_isTextured = false;
	m_isLit = false;

	m_metallic = 64.0f;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Quad::Create()
{

	GLfloat vertices[]{ -0.5f,  0.5f, 0.0f,
					     0.5f,  0.5f, 0.0f,
					     0.5f, -0.5f, 0.0f,
					    -0.5f, -0.5f, 0.0f };


	//----------------------------- Data that represents colors for quad


	GLfloat colors[]{ m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b,
					  m_color.r, m_color.g, m_color.b, };


	//data that represents indices for quad
	GLfloat uvs[]{ 0.0f, 0.0f,
				   1.0f, 0.0f,
				   1.0f, 1.0f,
				   0.0f, 1.0f };

	GLint indices[] = { 0, 1, 3, 3, 1, 2};

	m_material.CreateVertexArray();
	m_material.BindVertexArray();
	{
		m_material.CreateBuffer("vertexVBO");
		m_material.BindBuffer("vertexVBO");
		m_material.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(vertices, sizeof(vertices), "vertexIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("colorVBO");
		m_material.BindBuffer("colorVBO");
		m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(colors, sizeof(colors), "colorIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("TextureVBO");
		m_material.BindBuffer("TextureVBO");
		m_material.BufferSetAttribute("textureIn", 2, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(uvs, sizeof(uvs), "textureIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateElementBuffer(sizeof(indices), indices, GL_DYNAMIC_DRAW);
	}
	m_material.UnbindVertexArray();

	// Uniforms
	m_material.BindUniform("isTextured");
	m_material.BindUniform("model");
	m_material.BindUniform("isLit");
	m_material.BindUniform("material.ambient");
	m_material.BindUniform("material.diffuse");
	m_material.BindUniform("material.specular");
	m_material.BindUniform("material.metallic");

}

void Quad::Render()
{
	m_material.SendUniformData("isLit", 1);
	m_material.SendUniformData("isTextured", m_isTextured);
	m_material.SendUniformData("material.ambient", m_ambient);
	m_material.SendUniformData("material.diffuse", m_diffuse);
	m_material.SendUniformData("material.specular",m_specular);
	m_material.SendUniformData("material.metallic",m_metallic);
	m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());

	m_material.BindTexture();
	m_material.BindVertexArray();
	m_material.DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_material.UnbindVertexArray();
	m_material.UnbindTexture();

}
