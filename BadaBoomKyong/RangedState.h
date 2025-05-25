#pragma once
#include "BaseState.h"
class RangedState :
    public BaseState
{
public:
    RangedState(MONSTER_STATE _state=MONSTER_STATE::RANGE_ATTACK_STATE);
    virtual ~RangedState()override;
};

