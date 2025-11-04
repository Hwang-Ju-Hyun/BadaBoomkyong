#include "D_IsHPLessThan.h"
#include "Boss.h"
#include "BlackBoard.h"

D_IsHPLessThan::D_IsHPLessThan(BTNode* _child, float _hp)
    :m_pChild(_child)
    ,m_iHP(_hp)
{
}

D_IsHPLessThan::~D_IsHPLessThan()
{
}

BTNodeState D_IsHPLessThan::Enter(BlackBoard& _bb)
{    
     return BTNodeState::RUNNING;     
}

BTNodeState D_IsHPLessThan::Update(BlackBoard& _bb)
{
    // 조건 판단
    Boss* boss = _bb.GetBoss();
    float hp = boss->GetCurrentHP();
    if (hp < m_iHP)
        return BTNodeState::FAILURE; // 조건 불만족 시 FAIL

    // 조건 만족 → 자식 실행
    return m_pChild->Tick(_bb);
}

void D_IsHPLessThan::Exit(BlackBoard& _bb)
{
}

void D_IsHPLessThan::Abort()
{
}
