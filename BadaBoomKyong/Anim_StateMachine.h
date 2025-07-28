#pragma once
#include "Anim_IState.h"

template<typename T>
class AnimStateMachine
{
public:
	AnimStateMachine(T* _owner):m_pOwner(_owner),m_pCurrentAnimState(nullptr){}
	~AnimStateMachine() {}
public:
	void ChangeAnimState(AnimIState<T>* _newState)
	{
		if (m_pCurrentAnimState)
		{
			m_pCurrentAnimState->Exit(m_pOwner);
			delete m_pCurrentAnimState;			
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
};