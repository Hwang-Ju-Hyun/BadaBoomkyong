#include "WeightRandomSelector.h"
#include "MathUtil.h"

WeightedRandomSelector::WeightedRandomSelector(const std::vector<std::pair<BTNode*, float>>& _childNode)
{
	for (auto& n : _childNode)
	{
		m_vecWeightedNodes.push_back({ n.first, n.second });
	}
}

WeightedRandomSelector::~WeightedRandomSelector()
{
}

BTNodeState WeightedRandomSelector::Enter(BlackBoard& _bb)
{
    float totalWeight = 0.f;
    for (auto& wn : m_vecWeightedNodes)
        totalWeight += wn.weight;

    // 0~총 가중치 사이 랜덤 뽑기
    float r = MathUtil::GetInstance()->GetRandomNumber(0.f, totalWeight);

    // 어떤 노드를 선택할지 결정
    float cumulative = 0.f;
    m_pCurrentNode = nullptr;

    for (auto& wn : m_vecWeightedNodes)
    {
        cumulative += wn.weight;
        if (r <= cumulative)
        {
            m_pCurrentNode = wn.node;
            break;
        }
    }

    if (m_pCurrentNode == nullptr)
        return BTNodeState::FAILURE;

    return BTNodeState::RUNNING;
}

BTNodeState WeightedRandomSelector::Update(BlackBoard& _bb)
{
    if (m_pCurrentNode == nullptr)
        return BTNodeState::FAILURE;

    return m_pCurrentNode->Tick(_bb);
}

void WeightedRandomSelector::Exit(BlackBoard& _bb)
{
    m_pCurrentNode = nullptr;
}

void WeightedRandomSelector::Abort()
{
}
