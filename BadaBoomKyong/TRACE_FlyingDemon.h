#pragma once
#include "ITraceBehaviour.h"
#include <glm.hpp>

class FlyingDemon;
class RigidBody;
class Transform;
class Animator;
class Player;

class TRACE_FlyingDemon :
    public ITraceBehaviour
{
private:
    FlyingDemon* m_pFlyingDemon = nullptr;
    RigidBody* m_pRigidBody;
    Transform* m_pTransform;
    Player* m_pPlayer;
    Animator* m_pAnimator;
    glm::vec3 m_vPosition;
    glm::vec3 m_vPlayerPosition;
    glm::vec3 m_vTargetPosition;
    float m_fBaseY;
    bool m_bPatrolToTrace = true;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoTraceBehaviour(Monster* _mon)override;
};

