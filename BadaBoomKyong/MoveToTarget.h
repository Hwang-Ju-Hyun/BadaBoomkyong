#pragma once
#include "BehaviorTreeNode.h"

class MoveToTarget :
    public BTNode
{
public:
	MoveToTarget(Boss* _boss);
	virtual BTNodeState Enter();
	virtual BTNodeState Tick() ;
	virtual void Abort() ;

};

