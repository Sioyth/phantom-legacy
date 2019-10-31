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
	void BufferData(const GLvoid* data, const GLsizeiptr& dataSize, const GLchar* name, GLenum mode);
	void BufferSubData(GLenum target, const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data);
	void BufferSetAttribute(const GLchar* name, const GLint& size, GLenum type, GLboolean normalized, const GLsizei& stride);

	void UnbindBuffer();

public:
	
	void BindVertexArray();
	void UnbindVertexArray();
	void CreateVertexArray();
	void DrawVertexArray(GLenum mode, GLint first, const GLsizei& count);

public:

	void BindElementBuffer();
	void ElementBufferData();
	void CreateElementBuffer(const GLsizeiptr& dataSize, const GLvoid* data, GLenum mode);
	void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
	void UnbindElementBuffer();

private:

	std::map<std::string, GLuint> m_buffers;
	std::map<std::string, GLuint> m_attributes;

private:

	GLuint m_EBO;
	GLuint m_VAO;

	static GLuint s_shaderProgram;

};

