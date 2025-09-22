#pragma once
#include "IMeleeBehaviour.h"
#include <glm.hpp>

class FlyingDemon;
class RigidBody;
class Transform;
class Animator;
class Player;

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
	bool m_bDiveAttacking  = false;
	glm::vec3 target_pos;
	glm::vec3 dir;
private:
	FlyingDemon* m_pFlyingDemon = nullptr;
	RigidBody* m_pRigidBody;
	Transform* m_pTransform;
	Animator* m_pAnimator;
	glm::vec3 m_vPosition;
	Player* m_pPlayer;
private:
	float m_fTakeOffAccTime = 0.f;
	float m_fMaxTakingOffTime = 0.8f;
	bool m_bCanTakeOff = false;
};