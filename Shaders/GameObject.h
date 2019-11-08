#pragma once
#include <string>

#include <glm.hpp>
#include "glad/glad.h"

#include "Shader.h"
#include "Transform.h"

#include <iostream>

class GameObject
{

public:

	//GameObject(int j) {};

	virtual void Render() {};
	virtual void Update() {};		  	
	virtual void Create() {};

	bool LoadTexture(const std::string& filename, const std::string& textureName);

	void Translate(const glm::vec3& pos);
	void Translate(const float& x, const float& y, const float& z);

	void Rotate(const float& angle, const glm::vec3& rotAxis);
	//void Rotate(const float& angle, const float& x, const float& y, const float& z);

	void Scale(const glm::vec3& scale);
	void Scale(const float& x, const float& y, const float& z);


protected:

	bool m_isLit;
	bool m_enabled;
	bool m_isPicked;
	bool m_isTextured;

	std::string m_tag;
	std::string m_name;

	Shader m_shader;
	Transform m_transform;

};

