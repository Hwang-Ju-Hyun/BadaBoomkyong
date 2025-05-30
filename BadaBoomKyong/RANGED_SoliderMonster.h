#pragma once
#include "IRangedBehaviour.h"

class Bullet;
class SoldierMonster;


class RANGED_SoliderMonster :
    public IRangedBehaviour
{
private:
    SoldierMonster* m_pSoliderMonster = nullptr;   
    virtual void Init(Monster* _mon)override;
    virtual void DoRangedBehaviour(Monster* _mon)override;
public:    
    void MoveSideBySide_Attack();
    float m_fStepSum = 0.f;
    Bullet* m_pBullet = nullptr;
};

