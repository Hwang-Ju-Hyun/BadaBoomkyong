#pragma once
#include "BehaviorTreeNode.h"
class D_IsPlayerInsideMeleeRange:
	public BTNode
{
public:
    D_IsPlayerInsideMeleeRange(BTNode* _child);
    ~D_IsPlayerInsideMeleeRange();
public:
    virtual BTNodeState Enter(BlackBoard& _bb)override;
    virtual BTNodeState Update(BlackBoard& _bb)override;
    virtual void Exit(BlackBoard& _bb)override;
    virtual void Abort()override;
private:
    BTNode* m_pChild;
};

