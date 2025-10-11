#pragma once
#include "BehaviorTreeNode.h"

class Boss;

class MoveToTarget :
    public BTNode
{
public:
	MoveToTarget(Boss* _boss);
	virtual BTNodeState Enter(BlackBoard& _bb);
	virtual BTNodeState Tick(BlackBoard& _bb) ;
	virtual void Abort() ;

};

