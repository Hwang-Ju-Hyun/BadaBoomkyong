#pragma once
#include "IIdleBehaviour.h"
#include <glm.hpp>

class FlyingDemon;
class RigidBody;
class Transform;
class Animator;

class IDLE_FlyingDemon
	:public IIdleBehaviour
{
private:
	FlyingDemon* m_pFlyingDemon;
	RigidBody* m_pRigidBody;
	Transform* m_pTransform;
	Animator* m_pAnimator;
	glm::vec3 m_vPosition;
public:	
	virtual void Init(Monster* _mon);
	virtual void DoIdleBehaviour(Monster* _mon);
	virtual ~IDLE_FlyingDemon()override;
};

