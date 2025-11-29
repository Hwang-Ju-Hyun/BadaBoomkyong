#include "RangedState.h"
#include "Monster.h"
#include "GameObject.h"
#include <iostream>
#include "Transform.h"
#include "CurseDemonBullet.h"
#include "ObjectPoolManager.h"
#include "ObjectPool.h"
#include "EventManager.h"
#include "BulletFactory.h"

RangedState::RangedState(MONSTER_STATE _state)
	:BaseState(MONSTER_STATE::RANGE_ATTACK_STATE)
{

}

RangedState::~RangedState()
{
}

void RangedState::Init(Monster* _mon)
{
	if(_mon->GetRangedBehavior())
		_mon->GetRangedBehavior()->Init(_mon);
}

void RangedState::Update(Monster* _mon)
{	
	if (_mon->GetRangedBehavior())
		_mon->GetRangedBehavior()->DoRangedBehaviour(_mon);
}

void RangedState::Exit(Monster* _mon)
{
}