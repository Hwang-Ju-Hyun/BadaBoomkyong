#pragma once
#include "IIdleBehaviour.h"
class IDLE_Boss :
    public IIdleBehaviour
{
    virtual void DoIdleBehaviour(Monster* _mon)override;
};

