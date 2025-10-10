#include "MoveToTarget.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"

MoveToTarget::MoveToTarget(Boss* _boss)
	:m_pBoss(_boss)
{	

}
BTNodeState MoveToTarget::Enter()
{		
	return BTNodeState();
}

BTNodeState MoveToTarget::Tick()
{	

	glm::vec3 player_pos = m_pPlayerTransform->GetPosition();
	glm::vec3 boss_pos = m_pBossTransform->GetPosition();
	glm::vec3 dir = player_pos - boss_pos;
	dir = glm::normalize(dir);
	m_pBossTransform->AddPosition(dir * 100.f);
	
	if (GeometryUtil::GetInstance()->IsNear(boss_pos, player_pos))
		return BTNodeState::SUCCESS;
	return BTNodeState::RUNNING;
}

void MoveToTarget::Abort()
{
}

