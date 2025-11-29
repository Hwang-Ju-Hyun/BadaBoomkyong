#include "D_IsPlayerInsideMeleeRange.h"
#include "Boss.h"
#include "BlackBoard.h"

D_IsPlayerInsideMeleeRange::D_IsPlayerInsideMeleeRange(BTNode* _child)
    :m_pChild(_child)
{
}

D_IsPlayerInsideMeleeRange::~D_IsPlayerInsideMeleeRange()
{
}

BTNodeState D_IsPlayerInsideMeleeRange::Enter(BlackBoard& _bb)
{
    return BTNodeState::RUNNING;
}

BTNodeState D_IsPlayerInsideMeleeRange::Update(BlackBoard& _bb)
{
    // 조건 판단
    Boss* boss = _bb.GetBoss();
    if (!_bb.IsPlayerNearX(boss))
        return BTNodeState::FAILURE; // 조건 불만족 시 FAIL

    // 조건 만족 → 자식 실행
    return m_pChild->Tick(_bb);
}

void D_IsPlayerInsideMeleeRange::Exit(BlackBoard& _bb)
{
    m_pChild->Exit(_bb);
}

void D_IsPlayerInsideMeleeRange::Abort()
{
    m_pChild->Abort();
}
