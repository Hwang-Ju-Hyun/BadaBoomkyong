#pragma once
#include "IMeleeBehaviour.h"

class CurseDemon;

class MELEE_CurseDemon :
    public IMeleeBehaviour
{
private:
    CurseDemon* m_pCurseDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoMeleeBehaviour(Monster* _mon)override;    

    float m_fMeleeCoolTimeAcc = 0.f;
    float m_fMeleeAtkCoolTime = 0.f;
};