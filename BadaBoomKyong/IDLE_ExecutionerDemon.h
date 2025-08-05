#pragma once
#include "IIdleBehaviour.h"
class IDLE_ExecutionerDemon :
    public IIdleBehaviour
{
    virtual void DoIdleBehaviour(Monster* _mon)override;
};

