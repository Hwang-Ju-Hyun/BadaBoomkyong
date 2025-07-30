#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class Transform;
class Sprite;
class GameObject;
class Collider;
class RigidBody;
class AI;
class Player;
class IIdleBehaviour;
class IRangedBehaviour;
class IMeleeBehaviour;
class IPatrolBehaviour;

template<typename T>
class AnimStateMachine;

#include "Animator.h"

enum class MonsterAnimState
{
    IDLE,
    RANGE_ATTACK,
    NORMAL_ATTACK,
    DEATH
};

class Monster :
    public MonoBehaviour
{
public:
    Monster(GameObject* _owner);
    virtual ~Monster()override;    
protected:
    Transform* m_pTransform = nullptr;
    Sprite* m_pSprite = nullptr;
    Collider* m_pCollider = nullptr;
    RigidBody* m_pRigidBody = nullptr;
    AI* m_pAI = nullptr;
    AnimStateMachine<Monster>* m_pAnimStateMachine;
    Animator* m_pAnimator;
    MonsterAnimState m_eCurrentState;


    Player* m_pPlayer;
    Transform* m_pPlayerTransform = nullptr;
protected:
    glm::vec3 m_vPosition = {};
    glm::vec3 m_vPlayerPosition = {};
protected:
    IIdleBehaviour*   m_pIdleBehavior;
    IRangedBehaviour* m_pRangedBehavior;
    IMeleeBehaviour*  m_pMeleeBehaviour;
    IPatrolBehaviour* m_pPatrolBehaviour;
public:
    inline void SetIdleBehaviour(IIdleBehaviour* _behaviour) { m_pIdleBehavior = _behaviour; }
    inline void SetRangedBehaviour(IRangedBehaviour* _behaviour) { m_pRangedBehavior = _behaviour; }
    inline void SetMeleeBehaivour(IMeleeBehaviour* _behaviour) { m_pMeleeBehaviour = _behaviour; }
    inline void SetPatrolBehaviour(IPatrolBehaviour* _behaviour) { m_pPatrolBehaviour = _behaviour; }
    inline void SetAnimator(Animator* _anim) { m_pAnimator = _anim; }

    inline Player* GetPlayer()const { return m_pPlayer; }
    inline IIdleBehaviour* GetIdleBehavior() { return m_pIdleBehavior; }
    inline IRangedBehaviour* GetRangedBehavior() { return m_pRangedBehavior; }
    inline IMeleeBehaviour* GetMeleeBehaviour() { return m_pMeleeBehaviour; }
    inline IPatrolBehaviour* GetPatrolBehaviour() { return m_pPatrolBehaviour; }
    inline AI* GetAI()const { return m_pAI; }
    inline MonsterAnimState GetCurrentState()const { return m_eCurrentState; }
    inline Animator* GetAnimator()const { return m_pAnimator; }
    inline AnimStateMachine<Monster>* GetAnimStateMachine()const { return m_pAnimStateMachine; }
protected:
    float m_fSpeed = 0.f;
    float m_fJumpImpulse = 500.f;
    bool m_bIsGround = false;    
public:
    inline void SetIsGround(bool _ground) { m_bIsGround = _ground; }
    inline bool GetIsGround()const { return m_bIsGround; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }
    inline float GetSpeed()const { return m_fSpeed; }    
public:
    bool m_bCol=false;
public:
    static constexpr const char* SpeedName = "Speed";    
    static constexpr const char* JumpForceName = "JumpForce";
};