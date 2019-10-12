#pragma once
#include <string>
#include "Transform.h"

class GameObject
{
public:

	GameObject();

private:

	std::string m_tag;
	std::string m_name;

	Transform m_transform;

	//Shader m_shader;
};

