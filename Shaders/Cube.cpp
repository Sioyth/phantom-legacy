#include "Cube.h"

Cube::Cube()
{

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

	GLfloat colors3d[] = { 1.0f ,0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
					   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
					   0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
					   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
					   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
					   1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
					   1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f,
					   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
					   1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f
	};

	GLuint indices3d[] = { 0,  1,  3,  3,  1,  2,
						   4,  5,  7,  7,  5,  6,
						   8,  9,  11, 11, 9,  10,
						   12, 13, 15, 15, 13, 14,
						   16, 17, 19, 19, 17, 18,
						   20, 21, 23, 23, 21, 22
	};

	m_shader.CreateShader("Main.vert", "Main.frag");

	m_shader.CreateVertexArray();
	m_shader.BindVertexArray();

	m_shader.CreateBuffer("vertexVBO");
	m_shader.BindBuffer("vertexVBO");
	m_shader.BufferData(vertices3d, sizeof(vertices3d), "vertexIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateBuffer("colorVBO");
	m_shader.BindBuffer("colorVBO");
	m_shader.BufferData(colors3d, sizeof(colors3d), "colorIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.UnbindBuffer();

	m_shader.CreateElementBuffer(sizeof(indices3d), indices3d, GL_DYNAMIC_DRAW);

	m_shader.UnbindVertexArray();
}

void Cube::Render()
{
	m_shader.BindVertexArray();
	m_shader.BindUniform("model");
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_shader.DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	m_shader.UnbindVertexArray();
}
