#pragma once
#include "glad/glad.h"
#include <map>
#include <string>

class Buffer
{
public:

	Buffer();

public:

	void BufferData(const GLvoid* data, const GLchar* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
	void BindBuffer(std::string bufferName);
	void CreateBuffer(std::string bufferName);

	void UnbindBuffer();

public:

	void BindVAO();

private:

	std::map<std::string, GLuint> m_buffers;

private:

	static GLuint s_VAO;
	static GLuint s_shaderProgram;

};

