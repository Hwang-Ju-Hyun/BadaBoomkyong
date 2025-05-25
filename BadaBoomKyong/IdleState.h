#pragma once
#include "BaseState.h"
class IdleState :
    public BaseState
{
public:
    IdleState(MONSTER_STATE _state=MONSTER_STATE::IDLE_STATE);
    virtual ~IdleState()override;
public:
    virtual void Init()  override; 
    virtual void Update()override;
    virtual void Exit()  override;
};

