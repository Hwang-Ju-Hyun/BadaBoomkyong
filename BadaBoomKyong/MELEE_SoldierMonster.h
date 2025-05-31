#pragma once
#include "IMeleeBehaviour.h"

class SoldierMonster;

class MELEE_SoldierMonster :
    public IMeleeBehaviour
{
private:
    SoldierMonster* m_pSoliderMonster = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoMeleeBehaviour(Monster* _mon)override;    
};