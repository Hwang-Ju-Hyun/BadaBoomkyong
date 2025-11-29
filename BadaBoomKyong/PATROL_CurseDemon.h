#pragma once
#include "IPatrolBehaviour.h"

class CurseDemon;


class PATROL_CurseDemon :
    public IPatrolBehaviour
{
private:
    CurseDemon* m_pCurseDemon = nullptr;    
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
};

