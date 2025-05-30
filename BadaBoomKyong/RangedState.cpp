#include "RangedState.h"
#include "Monster.h"
#include "GameObject.h"
#include <iostream>
#include "Transform.h"
#include "ThrowingWeapon.h"
#include "ObjectPoolManager.h"
#include "ObjectPool.h"
#include "EventManager.h"

RangedState::RangedState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::RANGE_ATTACK_STATE)
{

}

RangedState::~RangedState()
{
}

void RangedState::Init()
{
	m_pThrowWeaponPool = static_cast<ObjectPool<ThrowingWeapon, 30>*>(ObjectPoolManager::GetInstance()->GetPool<ThrowingWeapon, 30>());
	ObjectPoolManager::GetInstance()->ReigistPool<ThrowingWeapon, 30>();
}

void RangedState::Update()
{	
	MoveSideBySide();
}

void RangedState::Exit()
{
}

void RangedState::MoveSideBySide()
{
	Monster* mon_comp = dynamic_cast<Monster*>(GetAI()->GetOwner()->FindComponent(Monster::MonsterTypeName));
	
	if (mon_comp != nullptr)
	{
		Transform* mon_trs = dynamic_cast<Transform*>(GetAI()->GetOwner()->FindComponent(Transform::TransformTypeName));		
		float move_speed = 0.05f;
		float pos = move_speed*mon_comp->GetDirection();		
		if (std::fabs(m_fStepSum) <= mon_comp->GetRangedMoveAtkRange().x)
		{
			mon_trs->AddPositionX(pos);				
		}
		else //범위를 넘어가면
		{
			//방향 봐꾸기
			mon_comp->SetDirection(mon_comp->GetDirection() * -1);
			m_fStepSum = 0.f;
			ThrowAttack();
		}
		m_fStepSum += pos;
	}
}

void RangedState::ThrowAttack()
{
	//todo 여기서 오류남 여기서 금욜부터 고치면 됌
	GameObject* throwWeapon_obj=m_pThrowWeaponPool->GetPool();
	EventManager::GetInstance()->SetActiveTrue(throwWeapon_obj);
	throwWeapon_comp = throwWeapon_obj->FindComponent<ThrowingWeapon>();
	throwWeapon_comp->SetThrowable(true);
}