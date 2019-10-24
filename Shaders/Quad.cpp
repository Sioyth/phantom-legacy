#include "Quad.h"

Quad::Quad()
{
}

void Quad::Create()
{

	GLfloat vertices[]{ -0.5f,  0.5f, 0.0f,
					     0.5f,  0.5f, 0.0f,
					     0.5f, -0.5f, 0.0f,
					    -0.5f, -0.5f, 0.0f };


	//----------------------------- Data that represents colors for quad


	GLfloat colors[]{ 1.0f, 1.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      1.0f, 1.0f, 1.0f };


	//data that represents indices for quad
	GLfloat uvs[]{ 0.0f, 0.0f,
				   1.0f, 0.0f,
				   1.0f, 1.0f,
				   0.0f, 1.0f };

	GLint indices[] = { 0, 1, 3, 3, 1, 2};

	m_shader.CreateShader("Main.vert", "Main.frag");

	m_texture.LoadTexture();

	m_shader.CreateVertexArray();
	m_shader.BindVertexArray();

	m_shader.CreateBuffer("vertexVBO");
	m_shader.BindBuffer("vertexVBO");
	m_shader.BufferData(vertices, sizeof(vertices), "vertexIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateBuffer("colorVBO");
	m_shader.BindBuffer("colorVBO");
	m_shader.BufferData(colors, sizeof(colors), "colorIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateBuffer("TextureVBO");
	m_shader.BindBuffer("TextureVBO");
	m_shader.BufferData(uvs, sizeof(uvs), "textureIn", 2, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateElementBuffer(sizeof(indices), indices, GL_DYNAMIC_DRAW);

	m_shader.UnbindVertexArray();

	// Uniforms
	m_shader.BindUniform("isTextured");
	m_shader.BindUniform("model");

}

void Quad::Render()
{
	m_shader.SendUniformData("isTextured", 1);

	m_texture.BindTexture();

	m_shader.BindVertexArray();
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_shader.DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_shader.UnbindVertexArray();

	m_texture.UnbindTexture();
}
