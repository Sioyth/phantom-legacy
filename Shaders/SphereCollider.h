#pragma once
#include <glm.hpp>

class SphereCollider
{
public:

	SphereCollider();
	~SphereCollider();

public:

	void Render(); // Debug Only

	float Overlap(const SphereCollider& second);
	bool IsColliding(const SphereCollider& second);

	void SetRadius(float radius);
	void SetPosition(glm::vec3 position);

	const float GetRadius();
	const glm::vec3 GetPosition();

private:

	float m_radius;
	float m_overlap;
	float m_distance;
	glm::vec3 m_position;
	glm::vec3 m_distanceVector;

};

