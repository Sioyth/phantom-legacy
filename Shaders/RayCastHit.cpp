#include "RayCastHit.h"

//-----------------------------------------------------------------------------
GameObject* RayCastHit::GetGameObject()
{
	return m_gameObject;
}

//-----------------------------------------------------------------------------
void RayCastHit::SetGameObject(GameObject* obj)
{
	m_gameObject = obj;
}
