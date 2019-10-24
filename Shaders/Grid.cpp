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
	const int TOTAL_BYTES_VBO = SIZE * QUADRANTS * BYTERS_PER_LINE;

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
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices); 
		m_shader.UnbindBuffer();

		m_shader.BindBuffer("colorVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_shader.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// positive x quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ SIZE - i, 0 ,  SIZE,
						  SIZE - i, 0 , -SIZE };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_shader.BindBuffer("vertexVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_shader.UnbindBuffer();

		m_shader.BindBuffer("colorVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_shader.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// Negative Z quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{  SIZE, 0 , -SIZE + i,
						  -SIZE, 0 , -SIZE + i };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_shader.BindBuffer("vertexVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_shader.UnbindBuffer();

		m_shader.BindBuffer("colorVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_shader.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// positive Z quad
	for (int i = 0; i < SIZE; i++)
	{
		GLint vertices[]{ SIZE, 0 ,  SIZE - i,
						 -SIZE, 0 ,  SIZE - i };

		GLfloat color[]{ m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b };

		m_shader.BindBuffer("vertexVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
		m_shader.UnbindBuffer();

		m_shader.BindBuffer("colorVBO");
		m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
		m_shader.UnbindBuffer();

		offset += BYTERS_PER_LINE;

	}

	// X Axis
	GLint vertices[]{ SIZE, 0, 0,
					 -SIZE, 0, 0 };

	GLfloat color[]{ 1.0f, 0.0f, 0.0f,
					 1.0f, 0.0f, 0.0f};

	m_shader.BindBuffer("vertexVBO");
	m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);
	m_shader.UnbindBuffer();

	m_shader.BindBuffer("colorVBO");
	m_shader.BufferSubData(GL_ARRAY_BUFFER, offset, sizeof(color), color);
	m_shader.UnbindBuffer();

	offset += BYTERS_PER_LINE;

	// Y Axis

	// Z Axis 
	/*GLint vertices[]{ 0, 0 ,  SIZE,
					  0, 0 , -SIZE };

	GLfloat color[]{ m_color.r, m_color.g, m_color.b,
				     m_color.r, m_color.g, m_color.b };*/



	



	m_totalVertices = offset / BYTERS_PER_VERTEX;

}

void Grid::Render()
{

	m_shader.BindUniform("isTextured");
	m_shader.SendUniformData("isTextured", 0);

	m_shader.BindVertexArray();
	m_shader.BindUniform("model");
	m_shader.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	m_shader.DrawVertexArray(GL_LINES, 0, m_totalVertices);
	m_shader.UnbindVertexArray();
}
