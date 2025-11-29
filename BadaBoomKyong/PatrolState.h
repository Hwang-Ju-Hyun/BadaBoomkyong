#pragma once
#include "BaseState.h"

class Monster;

class PatrolState :
    public BaseState
{
public:
    PatrolState(MONSTER_STATE _state = MONSTER_STATE::PATROL_STATE);
    virtual ~PatrolState()override;
public:
    virtual void Init(Monster* _mon)  override;
    virtual void Update(Monster* _mon)override;
    virtual void Exit(Monster* _mon)  override;
};

