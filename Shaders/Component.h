#pragma once
#include <string>

class Component
{

public:

	virtual void Update() = 0;

protected:

	bool m_enabled;
	std::string name;
};

