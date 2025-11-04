#include "IsPlayerFar.h"
#include "BlackBoard.h"
#include "Boss.h"

IsPlayerFar::IsPlayerFar(Boss* _boss)
	:m_pBoss(_boss)
{
}

BTNodeState IsPlayerFar::Enter(BlackBoard& _bb)
{
	return BTNodeState::RUNNING;
}

BTNodeState IsPlayerFar::Update(BlackBoard& _bb)
{
	if (_bb.IsPlayerNearX(m_pBoss))
		return BTNodeState::FAILURE;  // 가까우면 실패 (다음 루트 실행 가능)
	return BTNodeState::SUCCESS;      // 멀면 성공 → 다음 노드(이동 등) 진행
}

void IsPlayerFar::Exit(BlackBoard& _bb)
{
}

void IsPlayerFar::Abort()
{
}
