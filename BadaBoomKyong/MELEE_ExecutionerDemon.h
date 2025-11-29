#pragma once
#include "IMeleeBehaviour.h"

class ExecutionerDemon;

class MELEE_ExecutionerDemon :
    public IMeleeBehaviour
{
private:
    ExecutionerDemon* m_pExecutionerDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoMeleeBehaviour(Monster* _mon)override;    

};

