#pragma once
#include "Anim_IState.h"
#include <unordered_map>
#include <cassert>

template<typename T>
class AnimStateMachine
{
public:
	AnimStateMachine(T* _owner):m_pOwner(_owner),m_pCurrentAnimState(nullptr){}
	~AnimStateMachine() 
	{
		for (auto iter = m_hashAnimState.begin();iter != m_hashAnimState.end();iter++)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
public:
	void RegisterAnimState(int _enumState, AnimIState<T>* _valueState)
	{
		m_hashAnimState.insert({ _enumState,_valueState });
	}

	void ChangeAnimState(int _newState)
	{
		auto iter = m_hashAnimState.find(_newState);
		assert(iter != m_hashAnimState.end());
		ChangeAnimState(iter->second);
	}
	void ChangeAnimState(AnimIState<T>* _newState)
	{
		if (m_pCurrentAnimState)
		{
			m_pCurrentAnimState->Exit(m_pOwner);						
		}
			
		m_pCurrentAnimState = _newState;

		if(m_pCurrentAnimState)
			m_pCurrentAnimState->Enter(m_pOwner);
	}
	void Update()
	{		
		if (m_pCurrentAnimState)
			m_pCurrentAnimState->Update(m_pOwner);
	}
private:
	T* m_pOwner;
	AnimIState<T>* m_pCurrentAnimState;
	std::unordered_map<int, AnimIState<T>*> m_hashAnimState;
};