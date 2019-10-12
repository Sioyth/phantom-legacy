#include "Buffer.h"
#include "Shader.h"

GLuint Buffer::s_shaderProgram = Shader::Instance()->GetShaderProgram();

void Buffer::BufferData(const GLvoid* data, const GLchar* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride)
{
	GLint var = glGetAttribLocation(s_shaderProgram, name);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(var, size, type, normalized, stride, 0);
	glEnableVertexAttribArray(var);
}

void Buffer::BindBuffer(std::string bufferName)
{
	// Bind (selects) buffer 
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[bufferName]);

	// Enable Variables for use
	glEnableVertexAttribArray(m_buffers[bufferName]);

}

void Buffer::CreateBuffer(std::string bufferName)
{
	GLuint tempBuffer;
	
	// Generates Space in the Vram/memory for the buffer
	glGenBuffers(1, &tempBuffer);

	m_buffers[bufferName] = tempBuffer;

}

void Buffer::UnbindBuffer()
{
	glBindVertexArray(0);
}
