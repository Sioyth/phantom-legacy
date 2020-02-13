#pragma once
#include <string>

class Component
{

public:

	virtual void Update() = 0;

private:

	std::string name;
};

