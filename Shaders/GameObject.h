#pragma once
#include <string>

#include <glm.hpp>
#include "glad/glad.h"

#include "Shader.h"
#include "Transform.h"

class GameObject
{
public:

	GameObject();

public:

	virtual void Render();
	virtual void Update();

	virtual void Create();

	Shader& GetShader();

protected:

	bool m_enabled;

	std::string m_tag;
	std::string m_name;

	Shader m_shader;
	Transform m_transform;

};

