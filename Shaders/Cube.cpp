#include "Cube.h"

Cube::Cube()
{
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
}

void Cube::Create()
{
	GLfloat vertices3d[] = { -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
							  0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f
	};

	GLfloat colors3d[] = {m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
	};

	GLuint indices3d[] = { 0,  1,  3,  3,  1,  2,
						   4,  5,  7,  7,  5,  6,
						   8,  9,  11, 11, 9,  10,
						   12, 13, 15, 15, 13, 14,
						   16, 17, 19, 19, 17, 18,
						   20, 21, 23, 23, 21, 22
	};

	GLfloat UVs[] = {
		  0.5f, 0.667f, 0.75f, 0.667f, 0.5f, 0.333f, 0.75f, 0.333f,
		  0.0f, 0.667f, 0.25f, 0.667f, 0.0f, 0.333f, 0.25f, 0.333f,
		  0.25f, 1.0f, 0.5f ,1.0f, 0.25f, 0.667f, 0.5f, 0.667f,
		  0.25f, 0.333f, 0.5f, 0.333f, 0.25f, 0.0f, 0.5f, 0.0f,
		  0.25f, 0.667f, 0.5f , 0.667f, 0.25f, 0.333f, 0.5f, 0.333f,
		  0.75f, 0.667f, 1.0f, 0.667, 0.75f, 0.333f, 1.0f, 0.333f

					  };

	m_shader.CreateVertexArray();
	m_shader.BindVertexArray();

	m_shader.CreateBuffer("vertexVBO");
	m_shader.BindBuffer("vertexVBO");
	m_shader.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_shader.BufferData(vertices3d, sizeof(vertices3d), "vertexIn", GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateBuffer("colorVBO");
	m_shader.BindBuffer("colorVBO");
	m_shader.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_shader.BufferData(colors3d, sizeof(colors3d), "colorIn", GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateBuffer("TextureVBO");
	m_shader.BindBuffer("TextureVBO");
	m_shader.BufferSetAttribute("textureIn", 2, GL_FLOAT, GL_FALSE, 0);
	m_shader.BufferData(UVs, sizeof(UVs), "textureIn", GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateElementBuffer(sizeof(indices3d), indices3d, GL_DYNAMIC_DRAW);

	m_shader.UnbindVertexArray();

	// Uniforms
	m_shader.BindUniform("isTextured");
	m_shader.BindUniform("model");
}

void Cube::Update()
{
}

void Cube::Render()
{
	m_shader.SendUniformData("isTextured", 0);

	m_shader.BindTexture();

	m_shader.BindVertexArray();
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_shader.DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	m_shader.UnbindVertexArray();

	m_shader.UnbindTexture();
}
