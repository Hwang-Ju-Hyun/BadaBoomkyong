#pragma once
#include "BaseState.h"

#include "ObjectPool.h"
#include "IRangedBehaviour.h"

class Monster;
class CurseDemonBullet;
class BulletFactory;

class RangedState :
    public BaseState
{
public:
    RangedState(MONSTER_STATE _state=MONSTER_STATE::RANGE_ATTACK_STATE);
    virtual ~RangedState()override;
public:
    virtual void Init(Monster* _mon)  override;
    virtual void Update(Monster* _mon)override;
    virtual void Exit(Monster* _mon)  override;    
};

