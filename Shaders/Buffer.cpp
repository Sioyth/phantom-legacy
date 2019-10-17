#include "Buffer.h"
#include "Shader.h"
#include "Debug.h"

GLuint Buffer::s_shaderProgram = 0;

Buffer::Buffer()
{
	
}

void Buffer::BufferData(const GLvoid* data, const GLsizeiptr& dataSize, const GLchar* name, const GLint& size, GLenum type, GLboolean normalized, const GLsizei& stride, GLenum mode)
{
	// TEMPORARY SOLUTION
	s_shaderProgram = Shader::GetShaderProgram();

	m_attributes[name] = glGetAttribLocation(s_shaderProgram, name);
	
	if (m_attributes[name] == -1)
	{
		Debug::ErrorLog(name);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, mode);
		glVertexAttribPointer(m_attributes[name], size, type, normalized, stride, 0);
		glEnableVertexAttribArray(m_attributes[name]);
	}
}

void Buffer::BufferSubData(GLenum target, const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data)
{
	glBufferSubData(target, offset, size, data);
}

void Buffer::BindBuffer(std::string bufferName)
{
	if (m_buffers.find(bufferName) == m_buffers.end())
	{
		Debug::ErrorLog("Buffer Object doesn't exist, can't be binded!");
	}
	else
	{
		// Bind (selects) buffer 
		glBindBuffer(GL_ARRAY_BUFFER, m_buffers[bufferName]);

		//// Enable Variables for use
		//glEnableVertexAttribArray(m_buffers[bufferName]);
	}

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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::BindVertexArray()
{
	glBindVertexArray(m_VAO);
}

void Buffer::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void Buffer::CreateVertexArray()
{
	glGenVertexArrays(1, &m_VAO);
}

void Buffer::BindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void Buffer::CreateElementBuffer(const GLsizeiptr& dataSize, const GLvoid* data, GLenum mode)
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, mode);
}

void Buffer::UnbindElementBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
