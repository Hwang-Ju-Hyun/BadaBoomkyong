#pragma once
#include "BehaviorTreeNode.h"
#include <vector>
class WeightedRandomSelector : public BTNode
{
private:
    struct WeightedNode
    {
        BTNode* node;
        float weight;
    };

    std::vector<WeightedNode> m_vecWeightedNodes;
    BTNode* m_pCurrentNode = nullptr;

public:
    WeightedRandomSelector(const std::vector<std::pair<BTNode*, float>>& _childNode);
    virtual ~WeightedRandomSelector() ;

    virtual BTNodeState Enter(BlackBoard& _bb) override;
    virtual BTNodeState Update(BlackBoard& _bb) override;
    virtual void Exit(BlackBoard& _bb) override;
    virtual void Abort() override;
};