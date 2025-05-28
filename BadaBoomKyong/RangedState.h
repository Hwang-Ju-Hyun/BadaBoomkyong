#pragma once
#include "BaseState.h"
class RangedState :
    public BaseState
{
public:
    RangedState(MONSTER_STATE _state=MONSTER_STATE::RANGE_ATTACK_STATE);
    virtual ~RangedState()override;
public:
    virtual void Init()  override;
    virtual void Update()override;
    virtual void Exit()  override;    
public:
    //todo Áö¿ì¼À
    void MoveSideBySide();
    float sum = 0.f;
};

