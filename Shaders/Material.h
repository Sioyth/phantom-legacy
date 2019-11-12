#pragma once
#include <glm.hpp>
#include <string>

#include "Shader.h"
#include "glad/glad.h"

class Material
{
public: 

	Material();

public:

	void SetDefuse(glm::vec3 defuse);
	void SetAmbient(glm::vec3 ambient);
	void SetMetallic(GLfloat metallic);
	void SetSpecular(glm::vec3 specular);

public:

	//#--------------------------------# 
	//# Encapsulating Shader functions #
	//#--------------------------------# 

	// -------------------------------------------# Texture

	void BindTexture();
	bool LoadTexture(const std::string& filename, const std::string& textureName);
	void UnbindTexture();
	void UnloadTexture();

	// -------------------------------------------# Shader

	void BindUniform(const std::string& name);
	void SendUniformData(const std::string& name, GLint data);
	void SendUniformData(const std::string& name, GLfloat data);
	void SendUniformData(const std::string& name, glm::vec3 data);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
	void SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void SendUniformData(const std::string& name, GLsizei count, GLboolean transpose, const glm::mat4& matrix);

	// -------------------------------------------# Buffer

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

private:

	Shader m_material;

	GLfloat m_metallic; 
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

};

