#pragma once
#include "BehaviorTreeNode.h"
#include <vector>

class RandomSelector :
    public BTNode
{
public:
    RandomSelector(std::vector<BTNode*> _childNode);
    virtual ~RandomSelector()override;
private:
    std::vector<BTNode*> m_vecChildNode;
    std::vector<BTNode*> m_vecShuffle;
    int m_iCurrent = 0;
public:
    virtual BTNodeState Enter(BlackBoard& _bb)override;
    virtual BTNodeState Update(BlackBoard& _bb)override;
    virtual void Exit(BlackBoard& _bb)override;
    virtual void Abort()override;
};

