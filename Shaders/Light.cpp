#include "Light.h"
#include "Debug.h"

GLuint Light::s_totalLights = 0;

Light::Light(LightType type)
{
	m_isTextured = false;
	m_isLit = false;
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;

	if (type == DirectionalLight)
	{
		m_color = glm::vec3(0.3f);
		m_material.SetAmbient(glm::vec3(0.3f));
		m_material.SetDiffuse(glm::vec3(0.3f));
		m_material.SetSpecular(glm::vec3(0.3f));
	}

	m_attenuationConst = 1.0f;
	m_attenuationLinear = 0.027f;
	m_attenuationQuad = 0.0028;

	m_collider.SetDimension(glm::vec3(0.5f));

	m_lightNumber = s_totalLights++;
	m_lightNumberStr = std::to_string(m_lightNumber);

	m_lightType = type;

	for (auto it = Shader::GetPrograms().begin(); it != Shader::GetPrograms().end(); it++)
	{
		glUseProgram(it->second);
		m_material.BindUniform("lights[" + m_lightNumberStr + "].type");
		m_material.SendUniformData("lights[" + m_lightNumberStr + "].type", m_lightType);
		Shader::UseCurrentProgram();
	}
}

void Light::Create()
{
	GLfloat vertices[]{ 0.0f,  0.0f, 0.0f };

	GLfloat colors[]{ m_color.r, m_color.g, m_color.b };


	for (auto it = Shader::GetPrograms().begin(); it != Shader::GetPrograms().end(); it++)
	{
		glUseProgram(it->second);

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
		m_material.BindUniform("isLit");
		m_material.BindUniform("model");
		m_material.BindUniform("isTextured");
		m_material.BindUniform("lightsActiveNumber");
		m_material.BindUniform("lights[" + m_lightNumberStr + "].position");
		m_material.BindUniform("lights[" + m_lightNumberStr + "].ambient");
		m_material.BindUniform("lights[" + m_lightNumberStr + "].diffuse");
		m_material.BindUniform("lights[" + m_lightNumberStr + "].specular");

		if (m_lightType == PointLight)
		{
			m_material.BindUniform("lights[" + m_lightNumberStr + "].attenuationConst");
			m_material.BindUniform("lights[" + m_lightNumberStr + "].attenuationLinear");
			m_material.BindUniform("lights[" + m_lightNumberStr + "].attenuationQuad");

			m_material.SendUniformData("lights[" + m_lightNumberStr + "].attenuationConst", m_attenuationConst);
			m_material.SendUniformData("lights[" + m_lightNumberStr + "].attenuationLinear", m_attenuationLinear);
			m_material.SendUniformData("lights[" + m_lightNumberStr + "].attenuationQuad", m_attenuationQuad);
		}

		m_material.SendUniformData("lightsActiveNumber", (int)s_totalLights);
	}
		Shader::UseCurrentProgram();
}

void Light::Render()
{
	m_collider.SetPosition(m_transform.GetPosition());
	m_collider.CalculateMinMax();

	for (auto it = Shader::GetPrograms().begin(); it != Shader::GetPrograms().end(); it++)
	{
		glUseProgram(it->second);

		m_material.SendUniformData("isLit", m_isLit);
		m_material.SendUniformData("isTextured", m_isTextured);
		m_material.SendUniformData("model", 1, GL_FALSE, m_transform.GetTransformMatrix());

		m_material.SendUniformData("lights[" + m_lightNumberStr + "].position", m_transform.GetPosition());
		m_material.SendUniformData("lights[" + m_lightNumberStr + "].ambient", m_material.GetAmbient());
		m_material.SendUniformData("lights[" + m_lightNumberStr + "].diffuse", m_material.GetDiffuse());
		m_material.SendUniformData("lights[" + m_lightNumberStr + "].specular", m_material.GetSpecular());

	}
		Shader::UseCurrentProgram();

		m_material.BindVertexArray();
		glPointSize(20.0f); // TODO put this in shader class
		m_material.DrawVertexArray(GL_POINTS, 0, 1);

	
}

void Light::SetLightType(LightType type)
{
	m_lightType = type;

	for (auto it = Shader::GetPrograms().begin(); it != Shader::GetPrograms().end(); it++)
	{
		glUseProgram(it->second);
		m_material.BindUniform("lights[" + m_lightNumberStr + "].type");
		m_material.SendUniformData("lights[" + m_lightNumberStr + "].type", m_lightType);
	}

	Shader::UseCurrentProgram();
}

void Light::SetLightColor(glm::vec3 color)
{
	m_material.SetAmbient(color);
	m_material.SetDiffuse(color);
	m_material.SetSpecular(color);
	m_color = color;
}
