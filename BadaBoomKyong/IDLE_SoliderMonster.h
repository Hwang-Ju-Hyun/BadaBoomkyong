#pragma once
#include "IIdleBehaviour.h"
class IDLE_SoliderMonster :
    public IIdleBehaviour
{
    virtual void DoIdleBehaviour(Monster* _mon)override;
};