#pragma once
#include "IPatrolBehaviour.h"

class ExecutionerDemon;

class PATROL_ExecutionerDemon :
    public IPatrolBehaviour
{
private:
    ExecutionerDemon* m_pExecutionerDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

