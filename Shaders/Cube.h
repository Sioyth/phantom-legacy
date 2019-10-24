#pragma once
#include "GameObject.h"
#include "Texture.h"

class Cube : public GameObject
{
public:

	Cube();

	virtual void Render();
	virtual void Create();

private:

	Texture m_texture;
};

