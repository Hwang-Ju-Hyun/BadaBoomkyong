#pragma once
#include "IIdleBehaviour.h"
class IDLE_SmokeDemon :
    public IIdleBehaviour
{
public:    
    virtual void DoIdleBehaviour(Monster* _mon)override;
};

