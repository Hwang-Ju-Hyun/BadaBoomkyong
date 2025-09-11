#pragma once
#include "IMeleeBehaviour.h"
class MELEE_FlyingDemon :
    public IMeleeBehaviour
{
public:
	virtual void Init(Monster* _mon);
	virtual void DoMeleeBehaviour(Monster* _mon);
	virtual ~MELEE_FlyingDemon()override;
public:
	float m_fMeleeCoolTimeAcc = 0.f;
	float m_fMeleeAtkCoolTime = 0.f;
};