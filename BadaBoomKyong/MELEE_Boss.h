#pragma once
#include "IMeleeBehaviour.h"
#include <glm.hpp>

class FlyingDemon;
class RigidBody;
class Transform;
class Animator;
class Player;

class Boss;

class MELEE_Boss :
    public IMeleeBehaviour
{
public:
	virtual void Init(Monster* _mon);
	virtual void DoMeleeBehaviour(Monster* _mon);
	virtual ~MELEE_Boss()override;
public:
	float m_fMeleeCoolTimeAcc = 0.f;
	float m_fMeleeAtkCoolTime = 0.f;
	bool m_bDiveAttacking = false;
	glm::vec3 target_pos;
	glm::vec3 dir;
private:
	Boss* m_pBoss = nullptr;
	RigidBody* m_pRigidBody;
	Transform* m_pTransform;
	Animator* m_pAnimator;
	glm::vec3 m_vPosition;
	Player* m_pPlayer;
};

