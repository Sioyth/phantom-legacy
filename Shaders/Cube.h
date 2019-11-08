#pragma once
#include "Primitives.h"
#include "Texture.h"

class Cube : public Primitives
{
public:

	Cube();

	virtual void Render();
	virtual void Create();
	virtual void Update();

};

