#include "IsPlayerNear.h"
#include "BlackBoard.h"
#include "Boss.h"

IsPlayerNear::IsPlayerNear(Boss* _boss)
	:m_pBoss(_boss)
{
}

IsPlayerNear::~IsPlayerNear()
{
}

BTNodeState IsPlayerNear::Enter(BlackBoard& _bb)
{
	return BTNodeState::RUNNING;
}

BTNodeState IsPlayerNear::Update(BlackBoard& _bb)
{
	if (!_bb.IsPlayerNearX(m_pBoss))
		return BTNodeState::FAILURE;  // 가까우면 실패 (다음 루트 실행 가능)
	return BTNodeState::SUCCESS;      // 멀면 성공 → 다음 노드(이동 등) 진행
}

void IsPlayerNear::Exit(BlackBoard& _bb)
{
}

void IsPlayerNear::Abort()
{
}
