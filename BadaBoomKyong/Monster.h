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
class ITraceBehaviour;
class IMeleeBehaviour;
class UIPanel;

template<typename T>
class AnimStateMachine;

#include "Animator.h"

enum class MonsterAnimState
{
    IDLE,
    RANGE_ATTACK,
    NORMAL_ATTACK,
    WALK,
    HURT,
    TAKE_OFF,    
    FLYING,
    DIVE_START,
    DIVING,
    JUMP,
    FALL,
    JUMP_ATTACK,
    DASH,
    DISAPPEAR,
    APPEAR,
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
    //Player
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
    ITraceBehaviour* m_pTraceBehaviour;
protected:
    float m_fDirection = 1.f;          //Postive : Right | Negative : Left 
public:
    inline void SetDirection(float _dir) { m_fDirection = _dir; }
    inline float GetDirection()const { return m_fDirection; }
    void UpdateSpriteFlipX();
private:
    bool m_bIsHurting = false;
    bool m_bIsStagger = false;
public:
    inline void SetIsHurting(bool _hurt) { m_bIsHurting = _hurt; }
    inline bool GetIsHurting()const { return m_bIsHurting; }
    inline void SetIsStagger(bool _stagger) { m_bIsStagger = _stagger; }
    inline const bool GetIsStagger()const { return m_bIsStagger; }
public:
    inline void SetIdleBehaviour(IIdleBehaviour* _behaviour) { m_pIdleBehavior = _behaviour; }
    inline void SetRangedBehaviour(IRangedBehaviour* _behaviour) { m_pRangedBehavior = _behaviour; }
    inline void SetMeleeBehaivour(IMeleeBehaviour* _behaviour) { m_pMeleeBehaviour = _behaviour; }
    inline void SetPatrolBehaviour(IPatrolBehaviour* _behaviour) { m_pPatrolBehaviour = _behaviour; }
    inline void SetTraceBehaviour(ITraceBehaviour* _behaviour) { m_pTraceBehaviour = _behaviour; }    
    inline void SetAnimator(Animator* _anim) { m_pAnimator = _anim; }
    inline void SetAnimCurrentState(MonsterAnimState _eState) {
        if (m_eCurrentState == _eState) { return; }m_eCurrentState = _eState;
    }
    inline Player* GetPlayer()const { return m_pPlayer; }
    inline IIdleBehaviour* GetIdleBehavior() { return m_pIdleBehavior; }
    inline IRangedBehaviour* GetRangedBehavior() { return m_pRangedBehavior; }
    inline IMeleeBehaviour* GetMeleeBehaviour() { return m_pMeleeBehaviour; }
    inline IPatrolBehaviour* GetPatrolBehaviour() { return m_pPatrolBehaviour; }
    inline ITraceBehaviour* GetTraceBehaviour() { return m_pTraceBehaviour; }
    inline AI* GetAI()const { return m_pAI; }
    inline MonsterAnimState GetCurrentState()const { return m_eCurrentState; }
    inline Animator* GetAnimator()const { return m_pAnimator; }
    inline AnimStateMachine<Monster>* GetAnimStateMachine()const { return m_pAnimStateMachine; }
protected:
    float m_fSpeed = 0.f;
    float m_fJumpImpulse = 500.f;
    bool m_bIsGround = false;

    int m_iCurrentHP = 10;
    int m_iInitHP = 10;
    bool m_bIsAlive = true;

    float m_fMeleeAtkCoolTime = 0.f;
    float m_fRangeAtkCoolTime = 0.f;

    float m_fHitFlashDuration = 0.3f;
    float m_fHitFlashAccTime = 0.f;
    void OccurHitFlash();
public:        
    const std::string GetCurrentAnimState();
    inline void SetIsGround(bool _ground) { m_bIsGround = _ground; }
    inline bool GetIsGround()const { return m_bIsGround; }
    inline void SetCurrentAnimState(MonsterAnimState _eState) { m_eCurrentState = _eState; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }
    inline float GetSpeed()const { return m_fSpeed; }    
    inline void SetCurrentHP(int _hp) { m_iCurrentHP = _hp; }
    inline void MinusCurrentHp(int _hp) { m_iCurrentHP -= _hp; }
    inline int GetCurrentHP()const { return m_iCurrentHP; }
    inline void SetIsAlive(bool _alive) { m_bIsAlive = _alive; }
    inline bool GetIsAlive()const { return m_bIsAlive; }
    inline void SetMeleeAtkCoolTime(float _time) { m_fMeleeAtkCoolTime = _time; }
    inline float GetMeleeAtkCoolTime()const { return m_fMeleeAtkCoolTime; }
    inline void SetRangeAtkCoolTime(float _time) { m_fRangeAtkCoolTime = _time; }
    inline float GetRangeAtkCoolTime()const { return m_fRangeAtkCoolTime; }
    inline glm::vec3 GetPosition()const { return m_vPosition; }
    inline RigidBody* GetRigidBody()const { return m_pRigidBody; }    
public:
    bool m_bCol=false;
public:
    static constexpr const char* SpeedName = "Speed";    
    static constexpr const char* JumpForceName = "JumpForce";
    static constexpr const char* MeleeAtkCoolTimeName = "MeleeAtkCoolTime";
    static constexpr const char* RangeAtkCoolTimeName = "RangeAtkCoolTime";
public:
    void InitHPBarUi();
    UIPanel* m_pHPPanelUI;
    UIPanel* m_pHPPanelBorderUI;
};