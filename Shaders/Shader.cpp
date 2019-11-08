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

Shader::Shader(const std::string& filename, const std::string& textureName)
{
	// -------------------------------------------# Checks if program is already created

	if (!s_isProgramCreated)
	{
		CreateShaderProgram();
	}

	if (!m_texture.LoadTexture(filename, textureName))
	{
		Debug::ErrorLog(filename + " couldn't be loaded!");
	}
}

void Shader::CreateShader(std::string vertShader, std::string fragShader)
{
	// -------------------------------------------# Read Shader Files

	std::string vertShaderCode = ReadShader(vertShader);
	std::string fragShaderCode = ReadShader(fragShader);

	// -------------------------------------------# Compile Shaders and checks for errors

	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertShaderCode);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderCode);

	// -------------------------------------------# Attach Shaders

	glAttachShader(s_shaderProgram, vertexShader);
	glAttachShader(s_shaderProgram, fragmentShader);

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

void Shader::SendUniformData(const std::string& name, GLfloat data)
{
	if (m_uniforms.find(name) == m_uniforms.end())
	{
		Debug::ErrorLog(name + " Uniform couldn't be finded!");
	}
	else
	{
		glUniform1f(m_uniforms[name], data);
	}
}

void Shader::SendUniformData(const std::string& name, glm::vec3 data)
{
	if (m_uniforms.find(name) == m_uniforms.end())
	{
		Debug::ErrorLog(name + " Uniform couldn't be finded!");
	}
	else
	{
		glUniform3f(m_uniforms[name], data.x, data.y, data.z);
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

void Shader::SendUniformData(const std::string& name, int flag)
{
	if (m_uniforms.find(name) == m_uniforms.end())
	{
		Debug::ErrorLog(name + " Uniform couldn't be finded!");
	}
	else
	{
		glUniform1i(m_uniforms[name], flag);
	}
		
}

void Shader::SendUniformData(const std::string& name, GLsizei count, GLboolean transpose, const glm::mat4& matrix)
{
	if (m_uniforms.find(name) == m_uniforms.end())
	{
		Debug::ErrorLog(name + " Uniform couldn't be finded!");
	}
	else
	{
		glUniformMatrix4fv(m_uniforms[name], count, transpose, &matrix[0][0]);
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

void Shader::BindBuffer(std::string bufferName)
{
	m_buffer.BindBuffer(bufferName);
}

void Shader::CreateBuffer(std::string bufferName)
{
	m_buffer.CreateBuffer(bufferName);
}

void Shader::BufferData(const GLvoid* data, const GLsizeiptr& dataSize, const GLchar* name, GLenum mode)
{
	m_buffer.BufferData(data, dataSize, name, mode);
}

void Shader::BufferSubData(GLenum target, const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data)
{
	m_buffer.BufferSubData(target, offset, size, data);
}

void Shader::BufferSetAttribute(const GLchar* name, const GLint& size, GLenum type, GLboolean normalized, const GLsizei& stride)
{
	m_buffer.BufferSetAttribute(name, size, type, normalized, stride);
}

void Shader::UnbindBuffer()
{
	m_buffer.UnbindBuffer();
}

void Shader::BindVertexArray()
{
	m_buffer.BindVertexArray();
}

void Shader::UnbindVertexArray()
{
	m_buffer.UnbindVertexArray();
}

void Shader::CreateVertexArray()
{
	m_buffer.CreateVertexArray();
}

void Shader::DrawVertexArray(GLenum mode, GLint first, const GLsizei& count)
{
	m_buffer.DrawVertexArray(mode, first, count);
}

void Shader::BindElementBuffer()
{
	m_buffer.BindElementBuffer();
}

void Shader::ElementBufferData()
{
}

void Shader::CreateElementBuffer(const GLsizeiptr& dataSize, const GLvoid* data, GLenum mode)
{
	m_buffer.CreateElementBuffer(dataSize, data, mode);
}

void Shader::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	m_buffer.DrawElements(mode, count, type, indices);
}

void Shader::UnbindElementBuffer()
{
	m_buffer.UnbindElementBuffer();
}

void Shader::BindTexture()
{
	m_texture.BindTexture();
}

bool Shader::LoadTexture(const std::string& filename, const std::string& textureName)
{
	if (m_texture.LoadTexture(filename, textureName))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Shader::UnbindTexture()
{
	m_texture.UnbindTexture();
}

void Shader::UnloadTexture()
{
	m_texture.UnloadTexture();
}


