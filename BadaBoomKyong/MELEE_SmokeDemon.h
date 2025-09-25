#pragma once
#include "IMeleeBehaviour.h"

class SmokeDemon;

class MELEE_SmokeDemon :
    public IMeleeBehaviour
{
private:
    SmokeDemon* m_pSmokeDemon = nullptr;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoMeleeBehaviour(Monster* _mon)override;

};

