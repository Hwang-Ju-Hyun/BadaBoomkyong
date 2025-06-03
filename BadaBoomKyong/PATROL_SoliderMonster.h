#pragma once
#include "IPatrolBehaviour.h"

class SoldierMonster;

class PATROL_SoliderMonster :
    public IPatrolBehaviour
{
private:
    SoldierMonster* m_pSoldierMonster = nullptr;
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

