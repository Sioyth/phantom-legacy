#pragma once

#include <glm.hpp>

class AABB
{
public:

	AABB();
	~AABB();

public:

	void Update();
	void Render(); // debug only

	bool IsColliding(const AABB& second);

public:

	glm::vec3 Overlap(const AABB& second);

	void CalculateMinMax();
	void SetPosition(glm::vec3 position);
	void SetDimension(glm::vec3 dimension);

	const glm::vec3& GetMin();
	const glm::vec3& GetMax();

private:

	float m_distanceFromBound;

	glm::vec3 m_min;
	glm::vec3 m_max;

	glm::vec3 m_clamped;
	glm::vec3 m_overlap;
	glm::vec3 m_distance;
	glm::vec3 m_position;
	glm::vec3 m_dimension;
	glm::vec3 m_pointOnEdge;
	glm::vec3 m_halfDimension;
	glm::vec3 m_totalDimensions;
	glm::vec3 m_secondTotalDimensions;

};

