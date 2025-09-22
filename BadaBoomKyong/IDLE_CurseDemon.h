#pragma once
#include "IIdleBehaviour.h"
class IDLE_CurseDemon :
    public IIdleBehaviour
{    
    virtual void DoIdleBehaviour(Monster* _mon)override;
};