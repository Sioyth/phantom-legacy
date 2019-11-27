#pragma once
#include <glm.hpp>
#include <map>
#include <string>
#include "glad/glad.h"

#include "Buffer.h"
#include "Texture.h"

class Shader
{
public:

	Shader();
	Shader(const std::string& filename, const std::string& textureName);

public:

	static void UseCurrentProgram();
	static void UseShaderProgram(std::string shaderProgram);
	static void CreateShaderProgram(std::string shaderProgram);
	static void CreateShader(std::string vertShader, std::string fragShader, std::string shaderProgram);

	static std::string ReadShader(const std::string& shader);
	static GLuint CompileShader(GLuint shaderID, const std::string& shaderCode);

	void BindUniform(const std::string& name);
	void SendUniformData(const std::string& name, GLint data);
	void SendUniformData(const std::string& name, GLfloat data);
	void SendUniformData(const std::string& name, glm::vec3 data);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SendUniformData(const std::string& name, GLsizei count, GLboolean transpose, const glm::mat4& matrix);

	void ShutdownShaders();

public:

	static const std::map<std::string, GLuint>& GetPrograms();

public:

	// -------------------------------------------# VBO

	// TODO avoid doing copies
	void BindBuffer(std::string bufferName);
	void CreateBuffer(std::string bufferName);
	void BufferData(const GLvoid* data, const GLsizeiptr& dataSize, const GLchar* name, GLenum mode);
	void BufferSubData(GLenum target, const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data);
	void BufferSetAttribute(const GLchar* name, const GLint& size, GLenum type, GLboolean normalized, const GLsizei& stride);

	void UnbindBuffer();

	// -------------------------------------------# VAO

	void BindVertexArray();
	void UnbindVertexArray();
	void CreateVertexArray();
	void DrawVertexArray(GLenum mode, GLint first, const GLsizei& count);

	// -------------------------------------------# EBO

	void BindElementBuffer();
	void ElementBufferData();
	void CreateElementBuffer(const GLsizeiptr& dataSize, const GLvoid* data, GLenum mode);
	void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
	void UnbindElementBuffer();

	// -------------------------------------------#

public:

	// -------------------------------------------# Texture

	void BindTexture();
	bool LoadTexture(const std::string& filename, const std::string& textureName);
	void UnbindTexture();
	void UnloadTexture();

public:

	Buffer& GetBuffer();
	static const GLuint& GetShaderProgram(); // temporary solution

private:

	Buffer m_buffer;

	Texture m_texture;

	GLuint m_vertexShader;
	GLuint m_fragmentShader;

	std::string m_vertShaderCode;
	std::string m_fragShaderCode;

	std::map<std::string, GLuint> m_uniforms;

private:

	static GLuint s_shaderProgram;
	static bool s_isProgramCreated;

	static std::map<std::string, GLuint> s_programs;
};

