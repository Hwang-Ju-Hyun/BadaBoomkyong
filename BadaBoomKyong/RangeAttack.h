#pragma once
#include "BehaviorTreeNode.h"

class Player;
class Boss;

class RangeAttack :
    public BTNode
{
public:
	RangeAttack(Boss* _boss);
	virtual BTNodeState Enter(BlackBoard& _bb)override;
	virtual BTNodeState Update(BlackBoard& _bb)override;
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
public:
	float m_fElapse_AimingAccTime = 0.f;
	float m_fMaxAimingTime = 3.f;

	float m_fElapse_AimingDelayAccTime = 0.f;
	float m_fMaxAimingDelayTime = 0.8f;
	bool m_bAimingFlag = true;
};

