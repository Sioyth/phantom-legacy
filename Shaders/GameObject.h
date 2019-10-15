#pragma once
#include <string>

#include "Shader.h"
#include "Transform.h"

class GameObject
{
public:

	GameObject();

public:

	virtual void Render();
	virtual void Update();

	Shader& GetShader();

protected:

	bool m_enabled;

	std::string m_tag;
	std::string m_name;

	Shader m_shader;
	Transform m_transform;

};

