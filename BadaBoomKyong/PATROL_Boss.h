#pragma once
#include "IPatrolBehaviour.h"
class Boss;
class PATROL_Boss :
    public IPatrolBehaviour
{
private:
    Boss* m_pBoss = nullptr;
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

