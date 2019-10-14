#pragma once
#include <map>
#include <string>

#include "Buffer.h"
#include "glad/glad.h"

class Shader
{
public:

	Shader();

public:

	void CreateShaderProgram();
	void CreateShader(std::string vertShader, std::string fragShader);

	std::string ReadShader(const std::string& shader);
	GLuint CompileShader(GLuint shaderID, const std::string& shaderCode);

	void BindUniform(const std::string& name);

	void SendUniformData(const std::string& name, GLint data);
	void SendUniformData(const std::string& name, GLfloat data);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	void ShutdownShaders();

public:

	Buffer& GetBuffer();
	static const GLuint& GetShaderProgram();

private:

	Buffer m_buffer;

	GLuint m_vertexShader;
	GLuint m_fragmentShader;

	std::string m_vertShaderCode;
	std::string m_fragShaderCode;

	std::map<std::string, GLuint> m_uniforms;

private:

	static GLuint s_shaderProgram;
	static bool s_isProgramCreated;
};

