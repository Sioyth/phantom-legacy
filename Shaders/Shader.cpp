#include "Shader.h"
#include "Debug.h"
#include <fstream>

Shader* Shader::Instance()
{
	static Shader* s_Shader = new Shader;
	return s_Shader;
}

void Shader::CreateShader(std::string vertShader, std::string fragShader)
{
	// -------------------------------------------# Read Shader Files

	m_vertShaderCode = ReadShader(vertShader);
	m_fragShaderCode = ReadShader(fragShader);

	// -------------------------------------------# Compile Shaders and checks for errors

	m_vertexShader = CompileShader(GL_VERTEX_SHADER, m_vertShaderCode);
	m_fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_fragShaderCode);

	// -------------------------------------------# Attach Shaders

	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);

	// -------------------------------------------# Linking Shader Program

	glLinkProgram(m_shaderProgram);

	//Enable Shader Program
	glUseProgram(m_shaderProgram);

	GLint linkResult;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetProgramInfoLog(m_shaderProgram, 1000, &length, error);

		std::string errorLog = std::string(error);
		Debug::ErrorLog("Link Error: \n\n" + errorLog);
	}
	
}

GLuint Shader::CompileShader(GLuint shaderID, const std::string& shaderCode)
{

	GLuint id = glCreateShader(shaderID);
	const char* code = shaderCode.c_str();

	//bind vertex shader code with shader object
	glShaderSource(id, 1, &code, NULL);

	//compile vertex shader code
	glCompileShader(id);

	GLint compileResult;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetShaderInfoLog(shaderID, 1000, &length, error);

		std::string errorLog = std::string(error);
		Debug::ErrorLog("Compile Error - " + errorLog);
	}

	return id;
}

void Shader::CreateShaderProgram()
{
	// -------------------------------------------# Create Shader Program

	m_shaderProgram = glCreateProgram();

	if (m_shaderProgram == 0)
	{
		Debug::ErrorLog("Shader program couldn't be created!");
	}

}

std::string Shader::ReadShader(const std::string &shader)
{
	std::fstream file;
	std::string shaderCode;
	std::string currentLine;

	// -------------------------------------------# Reads Shader

	file.open(shader);

	if (!file)
	{
		Debug::ErrorLog("Couldn't open " + shader + "!");
	}

	// -------------------------------------------# Store Shader code

	while (!file.eof())
	{
		getline(file, currentLine);
		shaderCode += currentLine + "\n";
	}

	file.close();

	// -------------------------------------------# Cast string to GLchar*

	const GLchar* shaderFinalCode = (const GLchar*)(shaderCode.c_str());
	return shaderCode;

}

GLuint Shader::GetShaderProgram()
{
	return m_shaderProgram;
}

void Shader::ShutdownShaders()
{
	/*glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_shaderProgramID);*/
}


