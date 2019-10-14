#include "Cube.h"

Cube::Cube()
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

	m_shader.GetBuffer().CreateVertexArray();
	m_shader.GetBuffer().BindVertexArray();

	m_shader.GetBuffer().CreateBuffer("vertexVBO");
	m_shader.GetBuffer().BindBuffer("vertexVBO");
	m_shader.GetBuffer().BufferData(vertices3d, sizeof(vertices3d), "vertexIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.GetBuffer().UnbindBuffer();

	m_shader.GetBuffer().CreateBuffer("colorVBO");
	m_shader.GetBuffer().BindBuffer("colorVBO");
	m_shader.GetBuffer().BufferData(colors3d, sizeof(colors3d), "colorIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
	m_shader.GetBuffer().UnbindBuffer();

	m_shader.GetBuffer().CreateElementBuffer(sizeof(indices3d), indices3d, GL_DYNAMIC_DRAW);

	//m_shader.GetBuffer().UnbindVertexArray();

}

void Cube::Render()
{
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
