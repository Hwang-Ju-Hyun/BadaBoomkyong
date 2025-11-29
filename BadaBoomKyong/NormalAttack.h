#pragma once
#include "BehaviorTreeNode.h"

class Player;
class Boss;


class NormalAttack :
    public BTNode
{
public:
	NormalAttack(Boss* _boss);
	virtual ~NormalAttack()override;
	virtual BTNodeState Enter(BlackBoard& _bb)override;
	virtual BTNodeState Update(BlackBoard& _bb)override;
	virtual void Exit(BlackBoard& _bb)override;
	virtual void Abort();
};

