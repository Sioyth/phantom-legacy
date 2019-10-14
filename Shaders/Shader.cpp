#include "Shader.h"
#include "Debug.h"
#include <fstream>

GLuint Shader::s_shaderProgram;
bool Shader::s_isProgramCreated = false;

Shader::Shader()
{
	// -------------------------------------------# Checks if program is already created

	if (!s_isProgramCreated)
	{
		CreateShaderProgram();
	}

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

	glAttachShader(s_shaderProgram, m_vertexShader);
	glAttachShader(s_shaderProgram, m_fragmentShader);

	// -------------------------------------------# Linking Shader Program

	glLinkProgram(s_shaderProgram);

	//Enable Shader Program
	glUseProgram(s_shaderProgram);

	GLint linkResult;
	glGetProgramiv(s_shaderProgram, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetProgramInfoLog(s_shaderProgram, 1000, &length, error);

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

void Shader::BindUniform(const std::string& name)
{
	if (m_uniforms.find(name) == m_uniforms.end())
	{
		m_uniforms[name] = glGetUniformLocation(s_shaderProgram, (const GLchar*) name.c_str());
	}
}

void Shader::CreateShaderProgram()
{
	// -------------------------------------------# Create Shader Program

	s_shaderProgram = glCreateProgram();

	if (s_shaderProgram == 0)
	{
		Debug::ErrorLog("Shader program couldn't be created!");
	}
	else 
	{
		s_isProgramCreated = true;
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

Buffer& Shader::GetBuffer()
{
	return m_buffer;
}

const GLuint& Shader::GetShaderProgram()
{
	if (!s_isProgramCreated)
	{
		Debug::ErrorLog("Shader Program Not created!!");
	}
	else
	{
		return s_shaderProgram;
	}
}

void Shader::ShutdownShaders()
{
	/*glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_shaderProgramID);*/
}


