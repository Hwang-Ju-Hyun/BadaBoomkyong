#pragma once

class Monster;

class IMeleeBehaviour
{
public:
	virtual void Init(Monster* _mon) = 0;
	virtual void DoMeleeBehaviour(Monster* _mon) = 0;	
	virtual ~IMeleeBehaviour() = default;
public:
	float m_fMeleeCoolTimeAcc = 0.f;
	float m_fMeleeAtkCoolTime = 0.f;
};