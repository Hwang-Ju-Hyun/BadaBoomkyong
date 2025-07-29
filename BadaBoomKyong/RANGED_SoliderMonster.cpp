#include "RANGED_SoliderMonster.h"
#include "Transform.h"
#include "Sprite.h"
#include "AI.h"
#include "BaseState.h"
#include "GameObjectManager.h"
#include "BulletFactory.h"
#include "SoldierGrenade.h"
#include "SoldierMonster.h"

void RANGED_SoliderMonster::Init(Monster* _mon)
{	
	m_pSoliderMonster = dynamic_cast<SoldierMonster*>(_mon);
	assert(m_pSoliderMonster != nullptr);
}

void RANGED_SoliderMonster::DoRangedBehaviour(Monster* _mon)
{
	MoveSideBySide_Attack();
}

void RANGED_SoliderMonster::MoveSideBySide_Attack()
{	
	if (m_pSoliderMonster != nullptr)
	{					
		Transform* mon_trs = dynamic_cast<Transform*>(m_pSoliderMonster->GetOwner()->FindComponent(Transform::TransformTypeName));
		float move_speed = m_pSoliderMonster->GetSpeed();
		float move_scala = move_speed *m_pSoliderMonster->GetMoveDirection();
		if (std::fabs(m_fStepSum) <= m_pSoliderMonster->GetRangedMoveAtkRange().x)
		{			 
			mon_trs->AddPositionX(move_scala);
		}
		else //범위를 넘어가면
		{
			//방향 봐꾸기			
			m_pSoliderMonster->SetMoveDirection(m_pSoliderMonster->GetMoveDirection() * -1);
			m_fStepSum = 0.f;
			m_pSoliderMonster->Fire();
		}
		m_fStepSum += move_scala;
	}
}
