#include "RangedState.h"
#include "Monster.h"
#include "GameObject.h"
#include <iostream>
#include "Transform.h"

RangedState::RangedState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::RANGE_ATTACK_STATE)
{

}

RangedState::~RangedState()
{
}

void RangedState::Init()
{
}

void RangedState::Update()
{
	//std::cout << "RangedState" << std::endl;
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
		float move_speed = 0.5f;
		float pos = move_speed*mon_comp->GetDirection();		
		if (std::fabs(sum) <= mon_comp->GetRangedMoveAtkRange().x)
		{
			mon_trs->AddPositionX(pos);				
		}
		else //범위를 넘어가면
		{
			//방향 봐꾸기
			mon_comp->SetDirection(mon_comp->GetDirection() * -1);
			sum = 0.f;				
		}
		sum += pos;
	}
}
