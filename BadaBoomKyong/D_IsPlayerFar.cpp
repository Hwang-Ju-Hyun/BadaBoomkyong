#include "D_IsPlayerFar.h"
#include "Boss.h"
#include "BlackBoard.h"

D_IsPlayerFar::D_IsPlayerFar(BTNode* _child)
	:m_pChild(_child)
{
}

D_IsPlayerFar::~D_IsPlayerFar()
{
}

BTNodeState D_IsPlayerFar::Enter(BlackBoard& _bb)
{
	return BTNodeState::RUNNING;
}

#include <iostream>
BTNodeState D_IsPlayerFar::Update(BlackBoard& _bb)
{
    // 조건 판단
    Boss* boss = _bb.GetBoss();
    if (_bb.IsPlayerNearX(boss))
    {
        std::cout << "DecoNode Fail Player is near" << std::endl;
        return BTNodeState::FAILURE; // 조건 불만족 시 FAIL    
    }        
    // 조건 만족 → 자식 실행
    return m_pChild->Tick(_bb);
}

void D_IsPlayerFar::Exit(BlackBoard& _bb)
{
    // 자식도 필요하면 Exit 호출
    m_pChild->Exit(_bb);
}

void D_IsPlayerFar::Abort()
{
    m_pChild->Abort();
}
