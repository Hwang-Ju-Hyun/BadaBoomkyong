#pragma once
#include "BehaviorTreeNode.h"
class D_IsPlayerFar :
    public BTNode
{
public:
    D_IsPlayerFar(BTNode* _child);
    ~D_IsPlayerFar();
public:
    virtual BTNodeState Enter(BlackBoard& _bb)override;
    virtual BTNodeState Update(BlackBoard& _bb)override;
    virtual void Exit(BlackBoard& _bb)override;
    virtual void Abort()override;
private:
    BTNode* m_pChild;
};

