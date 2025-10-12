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

};

