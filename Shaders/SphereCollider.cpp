#include "SphereCollider.h"

SphereCollider::SphereCollider()
{
}


SphereCollider::~SphereCollider()
{
}

float SphereCollider::Overlap(const SphereCollider& second)
{
	// Distance Vector
	m_distanceVector = m_position - second.m_position;

	// 
	m_distance = glm::length(m_distanceVector);

	// Calculates Overlap Distance;
	m_overlap = (m_distance - m_radius - second.m_radius) / 2.0f;

	return m_overlap;
}

bool SphereCollider::IsColliding(const SphereCollider& second)
{
	// Distance Vector
	m_distanceVector = m_position - second.m_position;

	// 
	m_distance = glm::length(m_distanceVector);


	if (m_distance < m_radius + second.m_radius)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}

void SphereCollider::SetPosition(glm::vec3 position)
{
	m_position = position;
}

const float SphereCollider::GetRadius()
{
	return m_radius;
}

const glm::vec3 SphereCollider::GetPosition()
{
	return m_position;
}
