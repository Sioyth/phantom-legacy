#include "AABB.h"

AABB::AABB()
{
	m_min = glm::vec3(0.0f);
	m_max = glm::vec3(0.0f);

	m_position = glm::vec3(0.0f);
	m_dimension = glm::vec3(0.0f);

}


AABB::~AABB()
{
}

void AABB::Update()
{
	CalculateMinMax();
}

bool AABB::IsColliding(const AABB& second)
{

	if (m_max.x > second.m_min.x&& second.m_max.x > m_min.x&&
		m_max.y > second.m_min.y&& second.m_max.y > m_min.y&&
		m_max.z > second.m_min.z&& second.m_max.z > m_min.z)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool AABB::IsColliding(SphereCollider& second)
{
	//Distance Beetween The bounds
	m_distance = m_position - second.GetPosition();

	m_distanceFromBound = sqrt(m_distance.x * m_distance.x +
		m_distance.y * m_distance.y +
		m_distance.z * m_distance.z);

	// Half of the Widh, Height and depth
	m_halfDimension = m_dimension * .5f;

	// Clamps m_clamped = glm::clamp(m_distance, -m_halfDimension, m_halfDimension);
	m_clamped = glm::clamp(m_distance, -m_halfDimension, m_halfDimension);

	// nearest edge point
	m_pointOnEdge = m_position - m_clamped;

	return (glm::distance(second.GetPosition(), m_pointOnEdge) <= second.GetRadius());

}

glm::vec3 AABB::Overlap(const AABB& second)
{
	m_totalDimensions = m_min + m_max;
	m_secondTotalDimensions = second.m_min + second.m_max;

	// Checks which side is colliding. > 0 would be positive x,y,z values
	if (m_totalDimensions.x - m_secondTotalDimensions.x > 0 ||
		m_totalDimensions.y - m_secondTotalDimensions.y > 0 ||
		m_totalDimensions.z - m_secondTotalDimensions.z > 0)

		m_overlap = (-(m_totalDimensions - m_secondTotalDimensions) / 2.0f) / 2.0f;

	else
		m_overlap = ((m_totalDimensions - m_secondTotalDimensions) / 2.0f) / 2.0f;

	return m_overlap;
}

void AABB::CalculateMinMax()
{
	// Half of the Widh, Height and depth
	m_halfDimension = m_dimension / 2.0f;

	// Calculate Min 
	m_min.x = m_position.x - (m_halfDimension.x);
	m_min.y = m_position.y - (m_halfDimension.y);
	m_min.z = m_position.z - (m_halfDimension.z);

	// Calculate Max
	m_max.x = m_position.x + (m_halfDimension.x);
	m_max.y = m_position.y + (m_halfDimension.y);
	m_max.z = m_position.z + (m_halfDimension.z);
}

void AABB::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void AABB::SetDimension(glm::vec3 dimension)
{
	m_dimension = dimension;
}

const glm::vec3& AABB::GetMin()
{
	return m_min;
}

const glm::vec3& AABB::GetMax()
{
	return m_max;
}
