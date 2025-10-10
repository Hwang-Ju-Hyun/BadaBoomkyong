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
    virtual BTNodeState Enter()override;
    virtual BTNodeState Tick()override;
    virtual void Abort()override;
};

