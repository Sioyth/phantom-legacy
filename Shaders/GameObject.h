#pragma once
#include <string>

#include <glm.hpp>
#include "glad/glad.h"
#include <iostream>

#include "Shader.h"
#include "Material.h"
#include "Transform.h"
#include "AABB.h"
#include "Input.h"

#include "Model.h"
#include "TransformLine.h"

class GameObject
{

public:

	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Create() = 0;

public:

	bool LoadTexture(const std::string& filename, const std::string& textureName);

	void Translate(const glm::vec3& pos);
	void Translate(const float& x, const float& y, const float& z);

	void Rotate(const float& angle, const glm::vec3& rotAxis);
	//void Rotate(const float& angle, const float& x, const float& y, const float& z);

	void Scale(const glm::vec3& scale);
	void Scale(const float& x, const float& y, const float& z);

	void LoadModel(const std::string& filename);

	void Selected(); // TODO find better name

public:

	void SetIsSelected(bool flag) { m_isSelected = flag; };
	TransformLine* GetTransformLines();

	const glm::vec3& GetAmbient();
	const glm::vec3& GetDiffuse();
	const glm::vec3& GetSpecular();

	const glm::vec3& GetPosition();
	const glm::vec3& GetRotation();
	const glm::vec3& GetScale();

	const AABB& GetCollider() { return m_collider; };
	const AABB& GetTransformLineCollider();

	void SetIsLit(bool flag);
	bool GetIsLit();

	void SetPosition(glm::vec3 position);
	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);

protected:

	bool m_isLit;
	bool m_enabled;
	bool m_isSelected;
	bool m_isTextured;
	//bool m_light;

	std::string m_tag;
	std::string m_name;

	Model* m_model;
	Material m_material;
	Transform m_transform;
	TransformLine* m_transformLine;

	AABB m_collider;

private:

	glm::vec3 m_transformMidPoints[3];
};

