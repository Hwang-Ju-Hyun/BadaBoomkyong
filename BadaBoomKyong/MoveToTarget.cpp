#include "MoveToTarget.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"
#include "PlayerMelee.h"
#include "BlackBoard.h"

MoveToTarget::MoveToTarget(Boss* _boss)	
{	

}
BTNodeState MoveToTarget::Enter(BlackBoard& _bb)
{		
	return BTNodeState();
}

BTNodeState MoveToTarget::Tick(BlackBoard& _bb)
{			
	Player* p = _bb.GetPlayer();
	Boss* b = _bb.GetBoss();		

	glm::vec3 player_pos =p->GetPosition();
	b->SetTargetPos(player_pos);
	glm::vec3 boss_pos = b->GetPosition();

	if (GeometryUtil::GetInstance()->IsNear(boss_pos, player_pos))
		return BTNodeState::SUCCESS;
	return BTNodeState::RUNNING;
}

void MoveToTarget::Abort()
{
}

