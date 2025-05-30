#pragma once
#include "BaseState.h"
class IdleState :
    public BaseState
{
public:
    IdleState(MONSTER_STATE _state=MONSTER_STATE::IDLE_STATE);
    virtual ~IdleState()override;
public:
    virtual void Init(Monster* _mon)  override; 
    virtual void Update(Monster* _mon)override;
    virtual void Exit(Monster* _mon)  override;
};