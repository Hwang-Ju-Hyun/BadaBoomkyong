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

void RANGED_CurseDemon::MoveSideBySide_Attack()
{	
	if (m_pCurseDemon != nullptr)
	{					
		Transform* mon_trs = dynamic_cast<Transform*>(m_pCurseDemon->GetOwner()->FindComponent(Transform::TransformTypeName));
		float move_speed = m_pCurseDemon->GetSpeed();
		float move_scala = move_speed *m_pCurseDemon->GetMoveDirection();
		if (std::fabs(m_fStepSum) <= m_pCurseDemon->GetRangedMoveAtkRange().x)
		{			 
			mon_trs->AddPositionX(move_scala);
		}
		else //범위를 넘어가면
		{
			//방향 봐꾸기			
			m_pCurseDemon->SetMoveDirection(m_pCurseDemon->GetMoveDirection() * -1);
			m_fStepSum = 0.f;
			m_pCurseDemon->Fire();
		}
		m_fStepSum += move_scala;
	}
}
