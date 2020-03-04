#pragma once
#include "IComponent.h"
#include <stdint.h>


template<typename T>
class Component : public IComponent
{

public:

	static const size_t S_SIZE;
	static const size_t S_COMPONENT_TYPE_ID;

	static const size_t CREATE_COMPONENT(uint8_t& memory, EntityHandle entity, IComponent* comp);
	static const void FREE_COMPONENT(IComponent* comp);

protected:

	


private:

	

};

template<typename T>
const size_t Component<T>::CREATE_COMPONENT(uint8_t& memory, EntityHandle entity, IComponent* comp)
{
	size_t index = memory.size();
	memory.resize(index + Component<T>::SIZE);
	T* component = new(&memory[index])T(*(T*)comp);
	component->m_entityID = entity;

	return index;
}
//
//template<typename T>
//const void Component<T>::FREE_COMPONENT(IComponent* comp)
//{
//	T* component = (T*)comp;
//	component->
//}

template<typename T>
const size_t Component<T>::S_SIZE(sizeof(T));

template<typename T>
const size_t Component<T>::S_COMPONENT_TYPE_ID(IComponent::NextID());



