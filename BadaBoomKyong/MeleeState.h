#pragma once
#include "BaseState.h"
class MeleeState :
    public BaseState
{
    MeleeState(MONSTER_STATE _state = MONSTER_STATE::MELEE_ATTACK_STATE);
    virtual ~MeleeState()override;
};

