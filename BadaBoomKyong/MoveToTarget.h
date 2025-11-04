#pragma once
#include "BehaviorTreeNode.h"

class Boss;

class MoveToTarget :
    public BTNode
{
public:
	MoveToTarget(Boss* _boss);
	virtual BTNodeState Enter(BlackBoard& _bb)override;
	virtual BTNodeState Update(BlackBoard& _bb)override;
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort() ;
private:
	float m_fElapseAccTime = 0.f;
	float m_fMaxTime= 10.f;
	float m_fMaxDistance = 1300.f;
};

