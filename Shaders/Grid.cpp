#include "Grid.h"

Grid::Grid(GLuint size, GLfloat lineWidh, GLfloat r, GLfloat g, GLfloat b)
{
	m_size = size;
	m_lineWidth = lineWidh;
	
	m_color = glm::vec3(r, g, b);

}

void Grid::Create()
{

	GLuint offset = 0;

	const int SIZE = m_size;
	const int QUADRANTS = 4;
	const int BYTERS_PER_LINE = 6 * sizeof(GLfloat);
	const int BYTERS_PER_VERTEX = 3 * sizeof(GLfloat);
	const int TOTAL_BYTES_VBO = m_size * QUADRANTS * BYTERS_PER_LINE;

	//m_shader.CreateShader("Main.vert", "Main.frag");

	m_shader.CreateVertexArray();

	m_shader.BindVertexArray();
	{
		m_shader.CreateBuffer("vertexVBO");
		m_shader.BindBuffer("vertexVBO");
		m_shader.BufferData(nullptr, TOTAL_BYTES_VBO, "vertexIn", 3, GL_INT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
		m_shader.UnbindBuffer();

		m_shader.CreateBuffer("colorVBO");
		m_shader.BindBuffer("colorVBO");
		m_shader.BufferData(nullptr, TOTAL_BYTES_VBO, "colorIn", 3, GL_FLOAT, GL_FALSE, 0, GL_DYNAMIC_DRAW);
		m_shader.UnbindBuffer();
	}

	m_shader.UnbindVertexArray();

	// negative x axis lines
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ -SIZE + i, 0 ,  SIZE,
						  -SIZE + i, 0 , -SIZE };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_shader.BindBuffer("vertexVBO");
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		m_shader.BindBuffer("colorVBO");
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);

		offset += BYTERS_PER_LINE;

	}

	m_totalVertices = offset / BYTERS_PER_VERTEX;

}

void Grid::Render()
{
	m_shader.BindVertexArray();
	m_shader.BindUniform("model");
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	//glLineWidth(2.5f);
	glDrawArrays(GL_LINES, 0, m_totalVertices);
	m_shader.UnbindVertexArray();
}
