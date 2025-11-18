#include "RANGED_CurseDemon.h"
#include "Transform.h"
#include "Sprite.h"
#include "AI.h"
#include "BaseState.h"
#include "GameObjectManager.h"
#include "BulletFactory.h"
#include "CurseDemonBullet.h"
#include "CurseDemon.h"

void RANGED_CurseDemon::Init(Monster* _mon)
{	
	m_pCurseDemon = dynamic_cast<CurseDemon*>(_mon);
	assert(m_pCurseDemon != nullptr);
}

void RANGED_CurseDemon::DoRangedBehaviour(Monster* _mon)
{
	if(_mon->GetIsAlive())
		MoveSideBySide_Attack();
}
#include <iostream>
void RANGED_CurseDemon::MoveSideBySide_Attack()
{	
	if (m_pCurseDemon != nullptr)
	{							
		Transform* mon_trs = dynamic_cast<Transform*>(m_pCurseDemon->GetOwner()->FindComponent(Transform::TransformTypeName));
		float move_speed = m_pCurseDemon->GetSpeed();
		float move_scala = move_speed * m_pCurseDemon->GetMoveDirection();
		if (std::fabs(m_fStepSum) <= m_pCurseDemon->GetRangedMoveAtkRange().x&&movable)
		{			 
			mon_trs->AddPositionX(move_scala);
			if (m_pCurseDemon->GetCurrentState() == MonsterAnimState::RANGE_ATTACK
				&& m_pCurseDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pCurseDemon->SetCurrentAnimState(MonsterAnimState::IDLE);
			}			
		}
		else //범위를 넘어가면
		{
			//방향 봐꾸기			
			m_pCurseDemon->SetAnimCurrentState(MonsterAnimState::RANGE_ATTACK);
			movable = false;
			if (m_pCurseDemon->GetCurrentState() == MonsterAnimState::RANGE_ATTACK
				&& m_pCurseDemon->GetAnimator()->GetCurrentFrameIndex() == 11)
			{
				m_pCurseDemon->Fire();				
				m_pCurseDemon->SetMoveDirection(m_pCurseDemon->GetMoveDirection() * -1);
				movable = true;
			}
			
			m_fStepSum = 0.f;
			return;																		
		}
		m_fStepSum += move_scala;
	}
}
