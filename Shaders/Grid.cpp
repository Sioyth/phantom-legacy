#include "Grid.h"

Grid::Grid(GLuint size, GLfloat lineWidh, GLfloat r, GLfloat g, GLfloat b)
{
	m_size = size;
	m_lineWidth = lineWidh;
	
	m_color = glm::vec3(r, g, b);

	m_isLit = false;
	m_isTextured = false;

}

void Grid::Create()
{

	GLuint offset = 0;

	const int SIZE = m_size;
	const int QUADRANTS = 4;
	const int BYTERS_PER_LINE = 6 * sizeof(GLfloat);
	const int BYTERS_PER_VERTEX = 3 * sizeof(GLfloat);
	const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTERS_PER_LINE;

	//m_material.CreateShader("Main.vert", "Main.frag");

	m_material.CreateVertexArray();

	m_material.BindVertexArray();
	{
		m_material.CreateBuffer("vertexVBO");
		m_material.BindBuffer("vertexVBO");
		m_material.BufferSetAttribute("vertexIn", 3, GL_INT, GL_FALSE, 0);
		m_material.BufferData(nullptr, TOTAL_BYTES_VBO, "vertexIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("colorVBO");
		m_material.BindBuffer("colorVBO");
		m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(nullptr, TOTAL_BYTES_VBO, "colorIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();
	}

	m_material.UnbindVertexArray();

	// negative x axis lines
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ -SIZE + i, 0 ,  SIZE,
						  -SIZE + i, 0 , -SIZE };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_material.BindBuffer("vertexVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices); 
		m_material.UnbindBuffer();

		m_material.BindBuffer("colorVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_material.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// positive x quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ SIZE - i, 0 ,  SIZE,
						  SIZE - i, 0 , -SIZE };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_material.BindBuffer("vertexVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_material.UnbindBuffer();

		m_material.BindBuffer("colorVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_material.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// Negative Z quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{  SIZE, 0 , -SIZE + i,
						  -SIZE, 0 , -SIZE + i };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_material.BindBuffer("vertexVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_material.UnbindBuffer();

		m_material.BindBuffer("colorVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_material.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// positive Z quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ SIZE, 0 ,  SIZE - i,
						 -SIZE, 0 ,  SIZE - i };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_material.BindBuffer("vertexVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_material.UnbindBuffer();

		m_material.BindBuffer("colorVBO");
		m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_material.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// X Axis
	GLint vertices[]{ SIZE, 0, 0,
					 -SIZE, 0, 0 };

	GLfloat color[]{ 1.0f, 0.0f, 0.0f,
					 1.0f, 0.0f, 0.0f};

	m_material.BindBuffer("vertexVBO");
	m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
	m_material.UnbindBuffer();

	m_material.BindBuffer("colorVBO");
	m_material.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	m_material.UnbindBuffer();

	offset += BYTERS_PER_LINE;

	// Y Axis

	// Z Axis 
	/*GLint vertices[]{ 0, 0 ,  SIZE,
					  0, 0 , -SIZE };

	GLfloat color[]{ m_color.r, m_color.g, m_color.b,
				     m_color.r, m_color.g, m_color.b };*/

	m_totalVertices = offset / BYTERS_PER_VERTEX;
	m_material.BindUniform("isTextured");
	m_material.BindUniform("isLit");

}

void Grid::Render()
{

	
	m_material.SendUniformData("isLit", m_isLit);
	m_material.SendUniformData("isTextured", m_isTextured);

	m_material.BindVertexArray();
	m_material.BindUniform("model");
	m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_material.DrawVertexArray(GL_LINES, 0, m_totalVertices);
	m_material.UnbindVertexArray();
}
