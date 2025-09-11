#pragma once
#include "IPatrolBehaviour.h"

class FlyingDemon;

class PATROL_FlyingDemon :
    public IPatrolBehaviour
{
private:
    FlyingDemon* m_pFlyingDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

