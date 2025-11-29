#include "MoveToTarget.h"
#include "Transform.h"
#include "Boss.h"
#include "Player.h"
#include "GeometryUtill.h"
#include "PlayerMelee.h"
#include "BlackBoard.h"
#include "TimeManager.h"
#include "MathUtil.h"

MoveToTarget::MoveToTarget(Boss* _boss)	
{	

}
MoveToTarget::~MoveToTarget()
{
}
BTNodeState MoveToTarget::Enter(BlackBoard& _bb)
{		
	m_fElapseAccTime = 0.f;
	m_fMaxTime = 3.f;
	m_fMaxDistance = 1300.f;

	_bb.GetBoss()->SetCurrentAnimState(MonsterAnimState::WALK);

	return BTNodeState::RUNNING;	
}

BTNodeState MoveToTarget::Update(BlackBoard& _bb)
{			
	Player* p = _bb.GetPlayer();
	Boss* b = _bb.GetBoss();		

	glm::vec3 player_pos =p->GetPosition();
	b->SetTargetPos(player_pos);
	glm::vec3 boss_pos = b->GetPosition();
	
	float dt = TimeManager::GetInstance()->GetDeltaTime();
	m_fElapseAccTime += dt;
	std::cout << "Moving" << std::endl;
	//float dist = MathUtil::GetInstance()->DistanceBetweenX(boss_pos,player_pos);
	if (!GeometryUtil::GetInstance()->IsNearX(boss_pos, player_pos, 150.f))
	{
		if (/*dist >= m_fMaxDistance || */m_fElapseAccTime >= m_fMaxTime)
		{
			Abort();
			b->SetTargetPos(boss_pos);
			return BTNodeState::FAILURE;
		}
	}	
	if (GeometryUtil::GetInstance()->IsNearX(boss_pos, player_pos,150.f))
		return BTNodeState::SUCCESS;
	return BTNodeState::RUNNING;
}

void MoveToTarget::Exit(BlackBoard& _bb)
{
	Player* p = _bb.GetPlayer();
	Boss* b = _bb.GetBoss();

	glm::vec3 player_pos = p->GetPosition();
	glm::vec3 boss_pos = b->GetPosition();	
	std::cout << "Moving Exit" << std::endl;
}

void MoveToTarget::Abort()
{
	
	m_fElapseAccTime = 0.f;
}

