#pragma once
#include "glad/glad.h"
#include <string>

class Shader
{
public:

	static Shader* Instance();

public:

	void CreateShaderProgram();

	std::string ReadShader(const std::string& shader);
	GLuint CompileShader(GLuint shaderID, const std::string& shaderCode);
	void CreateShader(std::string vertShader, std::string fragShader);

	GLuint GetShaderProgram();

	void ShutdownShaders();

private:

	std::string m_vertShaderCode;
	std::string m_fragShaderCode;

	GLuint m_vertexShader;
	GLuint m_shaderProgram;
	GLuint m_fragmentShader;

private:

	Shader() {};
	Shader(const Shader&);
	Shader operator=(const Shader);
};

