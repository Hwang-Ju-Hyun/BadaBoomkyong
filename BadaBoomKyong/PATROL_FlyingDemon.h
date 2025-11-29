#pragma once
#include "IPatrolBehaviour.h"
#include <glm.hpp>


class FlyingDemon;
class RigidBody;
class Transform;
class Animator;

class PATROL_FlyingDemon :
    public IPatrolBehaviour
{
private:
    FlyingDemon* m_pFlyingDemon = nullptr;
    RigidBody* m_pRigidBody;
    Transform* m_pTransform;
    Animator* m_pAnimator;
    glm::vec3 m_vPosition;
public:
    virtual void Init(Monster* _mon)override;
    virtual void DoPatrolBehaviour(Monster* _mon)override;
    static bool Jump;
private:
    float m_fAccDegree;
};

