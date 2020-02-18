#pragma once
#include "Primitives.h"
#include "Texture.h"
#include "BoxCollider.h"

class Cube : public Primitives
{
public:

	Cube();

	virtual void Render();
	virtual void Create();
	virtual void Update();

private:

	BoxCollider* m_boxCollider;

};

