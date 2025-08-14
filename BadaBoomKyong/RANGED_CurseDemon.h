#pragma once
#include "IRangedBehaviour.h"

class Bullet;
class CurseDemon;


class RANGED_CurseDemon :
    public IRangedBehaviour
{
private:
    CurseDemon* m_pCurseDemon = nullptr;   
    virtual void Init(Monster* _mon)override;
    virtual void DoRangedBehaviour(Monster* _mon)override;
public:    
    void MoveSideBySide_Attack();
    float m_fStepSum = 0.f;
    Bullet* m_pBullet = nullptr;
    bool movable = true;
};

