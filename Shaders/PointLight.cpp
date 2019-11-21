#include "PointLight.h"
#include "Input.h"

PointLight::PointLight()
{
	m_isTextured = false;
	m_isLit = false;
	m_color.r = 1.0f;
	m_color.g = 0.0f;
	m_color.b = 0.0f;

	m_ambient = glm::vec3(0.0f, 1.0f, 1.0f);   //glm::vec3(0.2f, 0.2f, 0.2f);
	m_diffuse = glm::vec3(0.0f, 1.0f, 1.0f);   //glm::vec3(0.8f, 0.4f, 0.0f);
	m_specular = glm::vec3(0.0f, 1.0f, 1.0f);  //glm::vec3(0.4f, 0.3f, 0.1f);;
	
	m_attenuationConst = 1.0f;
	m_attenuationLinear = 0.15f;
	m_attenuationQuad = 2.0f;

	m_sphereCollider.SetRadius(2.0f);
	
}

void PointLight::Create()
{
	GLfloat vertices[]{ 0.0f,  0.0f, 0.0f };

	GLfloat colors[]{ m_color.r, m_color.g, m_color.b };

	m_material.CreateVertexArray();
	m_material.BindVertexArray();
	{
		m_material.CreateBuffer("vertexVBO");
		m_material.BindBuffer("vertexVBO");
		m_material.BufferSetAttribute("vertexIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(vertices, sizeof(vertices), "vertexIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

		m_material.CreateBuffer("colorVBO");
		m_material.BindBuffer("colorVBO");
		m_material.BufferSetAttribute("colorIn", 3, GL_FLOAT, GL_FALSE, 0);
		m_material.BufferData(colors, sizeof(colors), "colorIn", GL_DYNAMIC_DRAW);
		m_material.UnbindBuffer();

	}
	m_material.UnbindVertexArray();

	// Uniforms
	m_material.BindUniform("model");
	m_material.BindUniform("lightColor");
	m_material.BindUniform("isTextured");

	m_material.BindUniform("isLit");
	m_material.BindUniform("light.position");
	m_material.BindUniform("light.ambient");
	m_material.BindUniform("light.diffuse");
	m_material.BindUniform("light.specular");

	m_material.BindUniform("light.attenuationConst");
	m_material.BindUniform("light.attenuationLinear");
	m_material.BindUniform("light.attenuationQuad");

}

void PointLight::Render()
{

	m_sphereCollider.SetPosition(m_transform.GetPosition());

	m_material.SendUniformData("isTextured", m_isTextured);
	m_material.SendUniformData("isLit", m_isLit);
	m_material.SendUniformData("lightColor", m_color);

	m_material.SendUniformData("light.position", m_transform.GetPosition());
	m_material.SendUniformData("light.ambient",m_ambient);
	m_material.SendUniformData("light.diffuse", m_diffuse);
	m_material.SendUniformData("light.specular",m_specular);

	m_material.SendUniformData("light.attenuationConst", m_attenuationConst);
	m_material.SendUniformData("light.attenuationLinear", m_attenuationLinear);
	m_material.SendUniformData("light.attenuationQuad", m_attenuationQuad);

	m_material.BindVertexArray();
	m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());
	glPointSize(30.0f); // TODO put this in shader class
	glDrawArrays(GL_POINTS, 0, 1); // TODO put this in shader class.
	m_material.DrawVertexArray(GL_POINTS, 0, 1);

	float speed = 0.03f;

	// Camera Movement
	if (Input::Instance()->KeyDown(Keycode::UP))
	{
		m_transform.Translate(glm::vec3(0.0f, 0.0f, -1.0f) * speed);
	}

	if (Input::Instance()->KeyDown(Keycode::DOWN))
	{
		m_transform.Translate(glm::vec3(0.0f, 0.0f, 1.0f) * speed);
	}

	if (Input::Instance()->KeyDown(Keycode::LEFT))
	{
		m_transform.Translate(glm::vec3(-1.0f, 0.0f, 0.0f) * speed);
	}

	if (Input::Instance()->KeyDown(Keycode::RIGHT))
	{
		m_transform.Translate(glm::vec3(1.0f, 0.0f, 0.0f) * speed);
	}

	// Down
	if (Input::Instance()->KeyDown(Keycode::KP_4))
	{
		m_transform.Translate(glm::vec3(0.0f, 1.0f, 0.0f) * speed);
	}

	// Up
	if (Input::Instance()->KeyDown(Keycode::KP_1))
	{
		m_transform.Translate(glm::vec3(0.0f, -1.0f, 0.0f) * speed);
	}
}

const SphereCollider& PointLight::GetSphereCollider()
{
	return m_sphereCollider;
}
