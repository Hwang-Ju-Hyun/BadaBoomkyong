#pragma once
#include "BehaviorTreeNode.h"
#include <vector>

class Selector :
    public BTNode
{
public:
    Selector(std::vector<BTNode*> _childNode);
    virtual ~Selector()override;
private:
    std::vector<BTNode*> m_vecChildNode;
    int m_iCurrent = 0;
public:
    virtual BTNodeState Enter(BlackBoard& _bb)override;
    virtual BTNodeState Update(BlackBoard& _bb)override;
    virtual void Exit(BlackBoard& _bb)override;
    virtual void Abort()override;
};

