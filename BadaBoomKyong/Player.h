#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>
#include "Anim_StateMachine.h"
#include "Ray.h"

class Transform;
class Sprite;
class GameObject;
class Collider;
class RigidBody;
class BulletFactory;
class MeleeFactory;
class Bullet;
class Melee;
class Animator;
class HolySlashParticle;
class ParticleSystem;

enum PlayerAnimState
{ 
    IDLE,
    TOSPRINT,
    SPRINTING,
    JUMP,
    COMBO_ATTACK_1,
    COMBO_ATTACK_2,
    COMBO_ATTACK_3,
    HOLY_SLASH,
    RUN_ATTACK,
    JUMP_ATTACK,
    DASH,
    RUN_DASH,
    HEALING,
    HURT,
    FALL,
    LAND,
    DEATH    
};

enum class ComboStep
{
    NONE=0,
    COMBO_1,
    COMBO_2,
    COMBO_3
};

class Player :
    public MonoBehaviour
{
public:
    Player(GameObject* _owner);
    virtual ~Player()override;
private:
    Transform* m_pTransform = nullptr;
    Sprite* m_pSprite = nullptr;
    Collider* m_pCollider = nullptr;
    RigidBody* m_pRigidBody = nullptr;
    Animator* m_pAnimator = nullptr;
    AnimStateMachine<Player>* m_pAnimStateMachine;
private:
    Ray m_ray;
    RayCastHit m_rayHit;
    BulletFactory* m_pBulletFactory=nullptr;
    MeleeFactory* m_pMeleeFactory = nullptr;
    Bullet* m_pBullet=nullptr;
    Melee* m_pMelee=nullptr;
    PlayerAnimState m_ePreviousState;
    PlayerAnimState m_eCurrentState;
    bool m_bIsGround;
    bool m_bIsMoving;
    bool m_bHasLanded;
public:
    bool m_bHolySlashing = false;
private:
    ComboStep m_eComboStep = ComboStep::NONE;
    bool m_bComboQueue = false;
public:
    bool m_bInNormalCombo = false;
    float m_fComboMaxTimeOut = 1.f;
    static float m_fComboAccTime;
    int m_iComboIndex = 0;
private:
    int m_iInitHP = 5;
    int m_iCurrentHP=1;
    bool m_bIsAlive = true;
    //right : postive left : negative
    int m_iDir = 1;
    float m_fSpeed=0.f;            
    float m_fJumpImpulse = 500.f;   
    bool m_bNormalMeleeAttacking = false;
    bool m_bSprintMeleeAttacking = false;
    bool m_bJumpMeleeAttacking = false;
    bool m_bDashable = true;
    float m_fDashSpeed=600.f;
    float m_fDashDuration=0.4f;
    float m_fDashAccTime = 0.f;
    bool m_bIsDashing = false;
    bool m_bIsSprinting = false;
    bool m_bIsToSprint = false;
public:    
    inline Animator* GetAnimator()const { return m_pAnimator; }
    inline AnimStateMachine<Player>* GetAnimStateMachine()const { return m_pAnimStateMachine; }

    inline void SetDashable(bool _dash) { m_bDashable = _dash; }
    inline const bool GetDashable()const { return m_bDashable; }
    inline const bool GetIsDashing()const { return m_bIsDashing; }    
    inline Melee* GetMelee()const { return m_pMelee; }
    inline void AddHP(int _hp) { m_iCurrentHP += _hp; }
    inline void MinusCurrentHP(int _hp) { m_iCurrentHP -= _hp; }
    inline const int GetHP()const { return m_iCurrentHP; }
    inline void SetIsAlive(bool _alive) { m_bIsAlive = _alive; }
    inline const bool GetIsAlive()const { return m_bIsAlive; }
    inline void SetNormalMeleeAttacking(bool _attacking) { m_bNormalMeleeAttacking = _attacking; }
    inline const bool GetNormalMeleeAttacking()const { return m_bNormalMeleeAttacking; }
    inline void SetRunMeleeAttacking(bool _attacking) { m_bSprintMeleeAttacking = _attacking; }
    inline const bool GetRunMeleeAttacking()const { return m_bSprintMeleeAttacking; }
    inline void SetJumpMeleeAttacking(bool _attacking) { m_bJumpMeleeAttacking = _attacking; }
    inline const bool GetJumpMeleeAttacking()const { return m_bJumpMeleeAttacking; }
    inline const bool GetIsMoving()const { return m_bIsMoving; }
   
public:        
    int m_iCurJumpCount = 0;
    bool m_bCanMeleeAttack = false;
private:
    bool m_bIsFalling = false;
public:
    virtual void Init()override;
    virtual void Awake()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    //inline void SetJumpForce(float _force) { m_fJumpForce = _force; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }    
    inline void SetIsFalling(bool _fall) { m_bIsFalling = _fall; }
    inline float GetSpeed()const { return m_fSpeed; }
    inline void SetDir(int _dir) { m_iDir = _dir; }
    //inline float GetJumpForce()const { return m_fJumpForce; }
    inline void SetCanMeleeAttack(bool _canMelee) { m_bCanMeleeAttack = _canMelee; }
    inline bool GetCanMeleeAttack()const { return m_bCanMeleeAttack; }
    inline const bool GetIsFalling()const { return m_bIsFalling; }
    inline const int GetDir()const { return m_iDir; }
    inline const int GetCurrentState()const { return m_eCurrentState; }
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;    
private:
    void StateHandler();    
    void Jump();
    void Move();  
    void Fire();
    void MeleeAttack();
    void Dash();
    void Death();    
    void ComboUpdate();
private:
    bool m_bIsHurting = false;
public:
    void SetIsHurting(bool _hurt) { m_bIsHurting = _hurt; }
    bool GetIsHurting()const { return m_bIsHurting; }
public:
    static constexpr const char* PlayerTypeName = "Player";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpForceName = "JumpForce";
private:
    const char* GetComboClipName(ComboStep _step)const;
    void StartComboStep(ComboStep step);
    void AdvanceCombo();
    void EndCombo();
    void HolySlash();
public:
    HolySlashParticle* m_pHolySlashParticle;
    ParticleSystem* m_pPs;
public:
    static BaseRTTI* CreatePlayerComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;    
public:
    //temp :sholud delete
    bool jumpPressed = false;
    int m_iMaxJumpCount = 1;

private:
    bool m_bHolySlashFlag = false;
    float m_fMeleeDelayAccTime = 0.f;
};