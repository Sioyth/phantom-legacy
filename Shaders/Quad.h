#pragma once
#include "GameObject.h"
#include "Texture.h"

class Quad : public GameObject
{
public:

	Quad();

	virtual void Render();
	virtual void Create();

private:

	Texture m_texture;

};

