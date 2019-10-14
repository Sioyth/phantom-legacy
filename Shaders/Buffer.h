#pragma once
#include "glad/glad.h"
#include <map>
#include <string>

class Buffer
{
public:

	Buffer();

public:

	void BindBuffer(std::string bufferName);
	void CreateBuffer(std::string bufferName);
	void BufferData(const GLvoid* data, GLsizeiptr dataSize, const GLchar* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLenum mode);

	void UnbindBuffer();

public:
	
	void BindVertexArray();
	void UnbindVertexArray();
	void CreateVertexArray();

public:

	void BindElementBuffer();
	void ElementBufferData();
	void CreateElementBuffer(GLsizeiptr dataSize, const GLvoid* data, GLenum mode);
	void UnbindElementBuffer();

private:

	std::map<std::string, GLuint> m_buffers;
	std::map<std::string, GLuint> m_attributes;

private:

	GLuint m_EBO;
	GLuint m_VAO;

	static GLuint s_shaderProgram;

};

