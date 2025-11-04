#pragma once
#include "BehaviorTreeNode.h"
class D_IsHPLessThan :
    public BTNode
{
public:
    D_IsHPLessThan(BTNode* _child,float _hp);
    ~D_IsHPLessThan();
public:
    virtual BTNodeState Enter(BlackBoard& _bb)override;
    virtual BTNodeState Update(BlackBoard& _bb)override;
    virtual void Exit(BlackBoard& _bb)override;
    virtual void Abort()override;
private:
    BTNode* m_pChild;
    int m_iHP;
};

