#include "Quad.h"

Quad::Quad()
{
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
	m_isTextured = false;
	m_isLit = false;

	m_metallic = 1.0f;
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

		m_shader.CreateBuffer("TextureVBO");
		m_shader.BindBuffer("TextureVBO");
		m_shader.BufferSetAttribute("textureIn", 2, GL_FLOAT, GL_FALSE, 0);
		m_shader.BufferData(uvs, sizeof(uvs), "textureIn", GL_DYNAMIC_DRAW);
		m_shader.UnbindBuffer();

		m_shader.CreateElementBuffer(sizeof(indices), indices, GL_DYNAMIC_DRAW);
	}
	m_shader.UnbindVertexArray();

	// Uniforms
	m_shader.BindUniform("isTextured");
	m_shader.BindUniform("model");
	m_shader.BindUniform("isLit");
	m_shader.BindUniform("material.ambient");
	m_shader.BindUniform("material.diffuse");
	m_shader.BindUniform("material.specular");
	m_shader.BindUniform("material.metallic");

}

void Quad::Render()
{
	m_shader.SendUniformData("isTextured", m_isTextured);
	m_shader.SendUniformData("isLit", 1);

	m_shader.SendUniformData("material.ambient", m_ambient);
	m_shader.SendUniformData("material.diffuse", m_diffuse);
	m_shader.SendUniformData("material.specular",m_specular);
	m_shader.SendUniformData("material.metallic",m_metallic);

	m_shader.BindTexture();
	m_shader.BindVertexArray();
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_shader.DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_shader.UnbindVertexArray();
	m_shader.UnbindTexture();

}
