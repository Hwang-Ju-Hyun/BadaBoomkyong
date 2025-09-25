#pragma once
#include "IPatrolBehaviour.h"
class SmokeDemon;
class PATROL_SmokeDemon :
    public IPatrolBehaviour
{
private:
    SmokeDemon* m_pSmokeDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

