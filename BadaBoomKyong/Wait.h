#pragma once
#include "BehaviorTreeNode.h"

class GameObject;

class Wait :
    public BTNode
{
public:
	Wait(float _time=1.f);
	virtual ~Wait()override;
	virtual BTNodeState Enter(BlackBoard& _bb)override;
	virtual BTNodeState Update(BlackBoard& _bb)override;
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
private:
	float m_fWaitTime;
	float m_fAccTime=0.f;
public:
	inline void SetWaitTime(float _time) { m_fWaitTime = _time; }
};