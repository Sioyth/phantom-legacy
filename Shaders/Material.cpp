#include "Material.h"

Material::Material()
{
	m_metallic = 1.0f;
	m_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Material::SetDiffuse(glm::vec3 diffuse)
{
	m_diffuse = diffuse;
}

void Material::SetAmbient(glm::vec3 ambient)
{
	m_ambient = ambient;
}

void Material::SetMetallic(GLfloat metallic)
{
	m_metallic = metallic;
}

void Material::SetSpecular(glm::vec3 specular)
{
	m_specular = specular;
}

void Material::BindTexture()
{
	m_material.BindTexture();
}

bool Material::LoadTexture(const std::string& filename, const std::string& textureName)
{
	if (m_material.LoadTexture(filename, textureName))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Material::UnbindTexture()
{
	m_material.UnbindTexture();
}

void Material::UnloadTexture()
{
	m_material.UnloadTexture();
}

void Material::BindUniform(const std::string& name)
{
	m_material.BindUniform(name);
}

void Material::SendUniformData(const std::string& name, GLint data)
{
	m_material.SendUniformData(name, data);
}

void Material::SendUniformData(const std::string& name, GLfloat data)
{
	m_material.SendUniformData(name, data);
}

void Material::SendUniformData(const std::string& name, glm::vec3 data)
{
	m_material.SendUniformData(name, data);
}

void Material::SendUniformData(const std::string& name, GLfloat x, GLfloat y)
{
	m_material.SendUniformData(name, x, y);
}

void Material::SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
{
	m_material.SendUniformData(name, x, y, z);
}

void Material::SendUniformData(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	m_material.SendUniformData(name, x, y, z, w);
}

void Material::SendUniformData(const std::string& name, GLsizei count, GLboolean transpose, const glm::mat4& matrix)
{
	m_material.SendUniformData(name, count, transpose, matrix);
}

void Material::BindBuffer(std::string bufferName)
{
	m_material.BindBuffer(bufferName);
}

void Material::CreateBuffer(std::string bufferName)
{
	m_material.CreateBuffer(bufferName);
}

void Material::BufferData(const GLvoid* data, const GLsizeiptr& dataSize, const GLchar* name, GLenum mode)
{
	m_material.BufferData(data, dataSize, name, mode);
}

void Material::BufferSubData(GLenum target, const GLintptr& offset, const GLsizeiptr& size, const GLvoid* data)
{
	m_material.BufferSubData(target, offset, size, data);
}

void Material::BufferSetAttribute(const GLchar* name, const GLint& size, GLenum type, GLboolean normalized, const GLsizei& stride)
{
	m_material.BufferSetAttribute(name, size, type, normalized, stride);
}

void Material::UnbindBuffer()
{
	m_material.UnbindBuffer();
}

void Material::BindVertexArray()
{
	m_material.BindVertexArray();
}

void Material::UnbindVertexArray()
{
	m_material.UnbindVertexArray();
}

void Material::CreateVertexArray()
{
	m_material.CreateVertexArray();
}

void Material::DrawVertexArray(GLenum mode, GLint first, const GLsizei& count)
{
	m_material.DrawVertexArray(mode, first, count);
}

void Material::BindElementBuffer()
{
	m_material.BindElementBuffer();
}

void Material::ElementBufferData()
{
	m_material.ElementBufferData();
}

void Material::CreateElementBuffer(const GLsizeiptr& dataSize, const GLvoid* data, GLenum mode)
{
	m_material.CreateElementBuffer(dataSize, data, mode);
}

void Material::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
	m_material.DrawElements(mode, count, type, indices);
}

void Material::UnbindElementBuffer()
{
	m_material.UnbindElementBuffer();
}
