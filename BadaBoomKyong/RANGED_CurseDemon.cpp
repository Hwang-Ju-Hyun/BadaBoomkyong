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
		}
		else //������ �Ѿ��
		{
			//���� ���ٱ�			
			if (m_pCurseDemon->GetAnimator()->GetAnimation()->m_bLoopCount >= 1)
			{
				m_pCurseDemon->SetMoveDirection(m_pCurseDemon->GetMoveDirection() * -1);
				m_pCurseDemon->Fire();
				movable = true;
				m_fStepSum = 0.f;
				return;
			}			
			
			m_pCurseDemon->SetAnimCurrentState(MonsterAnimState::RANGE_ATTACK);			
			movable = false;													
		}
		m_fStepSum += move_scala;
	}
}
