#pragma once
#include "BehaviorTreeNode.h"
#include <vector>

class Sequence :
    public BTNode
{
public:
    Sequence(std::vector<BTNode*> _childNode);
    ~Sequence()override;
private:
    std::vector<BTNode*> m_vecChildNode;
    int m_iCurrent = 0;
public:
    virtual BTNodeState Enter()override;
    virtual BTNodeState Tick()override;
    virtual void Abort()override;
};

