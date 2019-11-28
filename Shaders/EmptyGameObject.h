#pragma once
#include "GameObject.h"
#include "Model.h"

class EmptyGameObject : public GameObject
{
public:

	EmptyGameObject();

	virtual void Create();
	virtual void Render();
	virtual void Update() {};

	void LoadModel(const std::string& filename);

private:

	Model* m_model;
	
};

