#pragma once
#include "header.h"

class AI;

class BaseState
{
public:
	BaseState() = delete;
	BaseState(MONSTER_STATE _state);
	virtual ~BaseState();	
private:
	MONSTER_STATE m_eState;
	AI* m_pAI=nullptr;
public:
	virtual void Init()=0;
	virtual void Update()=0;
	virtual void Exit()=0;
public:
	inline void SetAI(AI* _ai) { m_pAI = _ai; }
	inline AI* GetAI()const { return m_pAI; }
	inline MONSTER_STATE GetType() { return m_eState; }
};

