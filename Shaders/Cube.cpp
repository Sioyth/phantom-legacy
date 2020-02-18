#include "Cube.h"
#include "PhantomPhysX.h"
#include <vector>

Cube::Cube()
{
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;

	m_isLit = true;
	m_isTextured = false;
	m_collider.SetDimension(glm::vec3(1.0f));
	m_transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void Cube::Create()
{
	m_enabled = true;

	GLfloat vertices3d[] = { -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
							 -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f,
							  0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f,
							 -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f,
							  0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
							  0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f
	};

	GLfloat colors3d[] = {m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
						  m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
	};

	GLuint indices3d[] = { 0,  1,  3,  3,  1,  2,
						   4,  5,  7,  7,  5,  6,
						   8,  9,  11, 11, 9,  10,
						   12, 13, 15, 15, 13, 14,
						   16, 17, 19, 19, 17, 18,
						   20, 21, 23, 23, 21, 22
	};

	GLfloat UVs[] = {
		  0.5f, 0.667f, 0.75f, 0.667f, 0.5f, 0.333f, 0.75f, 0.333f,
		  0.0f, 0.667f, 0.25f, 0.667f, 0.0f, 0.333f, 0.25f, 0.333f,
		  0.25f, 1.0f, 0.5f ,1.0f, 0.25f, 0.667f, 0.5f, 0.667f,
		  0.25f, 0.333f, 0.5f, 0.333f, 0.25f, 0.0f, 0.5f, 0.0f,
		  0.25f, 0.667f, 0.5f , 0.667f, 0.25f, 0.333f, 0.5f, 0.333f,
		  0.75f, 0.667f, 1.0f, 0.667, 0.75f, 0.333f, 1.0f, 0.333f

	};

	GLfloat normals[] = { 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
						  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, //front face
						  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,
						  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, -1.0f, //back face
						 -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
						 -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, //left face
						  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
						  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, //right face
						  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
						  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, //top face
						  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
						  0.0f, -1.0f,  0.0f,  0.0f, -1.0f,  0.0f  //bottom face

	}; 

	m_material.CreateVertexArray();
	m_material.BindVertexArray();

	m_material.CreateBuffer("vertexVBO");
	m_material.BindBuffer("vertexVBO");
	m_material.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_material.BufferData(vertices3d, sizeof(vertices3d), "vertexIn", GL_DYNAMIC_DRAW);
	m_material.UnbindBuffer();

	m_material.CreateBuffer("colorVBO");
	m_material.BindBuffer("colorVBO");
	m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
	m_material.BufferData(colors3d, sizeof(colors3d), "colorIn", GL_DYNAMIC_DRAW);
	m_material.UnbindBuffer();

	m_material.CreateBuffer("TextureVBO");
	m_material.BindBuffer("TextureVBO");
	m_material.BufferSetAttribute("textureIn", 2, GL_FLOAT, GL_FALSE, 0);
	m_material.BufferData(UVs, sizeof(UVs), "textureIn", GL_DYNAMIC_DRAW);
	m_material.UnbindBuffer();

	m_material.CreateElementBuffer(sizeof(indices3d), indices3d, GL_DYNAMIC_DRAW);

	m_material.UnbindVertexArray();

	// Uniforms
	m_material.BindUniform("isLit");
	m_material.BindUniform("model");
	m_material.BindUniform("isTextured");

	m_material.BindUniform("material.ambient");
	m_material.BindUniform("material.diffuse");
	m_material.BindUniform("material.specular");
	m_material.BindUniform("material.metallic");

	m_boxCollider = new BoxCollider(m_transform);

}

void Cube::Update()
{
	if (m_enabled)
	{
		m_boxCollider->Update();
	}
}

void Cube::Render()
{

	if (m_enabled)
	{

		m_collider.SetPosition(m_transform.GetPosition());
		m_collider.CalculateMinMax();

		m_material.SendUniformData("isLit", m_isLit);
		m_material.SendUniformData("isTextured", m_isTextured);

		m_material.SendUniformData("material.ambient", m_material.GetAmbient());
		m_material.SendUniformData("material.diffuse", m_material.GetDiffuse());
		m_material.SendUniformData("material.specular", m_material.GetSpecular());
		m_material.SendUniformData("material.metallic", m_material.GetMetallic());

		m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());

		//m_material.BindTexture();

		m_material.BindVertexArray();
		m_material.DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		m_material.UnbindVertexArray();

		//m_material.UnbindTexture();

	}

}
