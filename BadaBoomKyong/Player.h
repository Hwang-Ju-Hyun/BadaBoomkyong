#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

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

enum PlayerAnimState
{
    IDLE,
    RUN,
    JUMP,
    ATTACK,
    RUN_ATTACK,
    HEALING,
    FALL,
    DEATH    
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
private:
    BulletFactory* m_pBulletFactory=nullptr;
    MeleeFactory* m_pMeleeFactory = nullptr;
    Bullet* m_pBullet=nullptr;
    Melee* m_pMelee=nullptr;
    PlayerAnimState m_ePreviousState;
    PlayerAnimState m_eCurrentState;
public:
    bool melee = false;
private:
    //right : postive left : negative
    int m_iDir = 1;
    float m_fSpeed=0.f;            
    float m_fJumpImpulse = 500.f;    
public:        
    int m_iCurJumpCount = 0;
private:
    bool m_bCanMeleeAttack = false;
    bool m_bIsFalling = false;
public:
    virtual void Init()override;
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
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;    
private:
    void AnimationHandle();
    void Jump();
    void Move();  
    void Fire();
    void MeleeAttack();    
public:
    static constexpr const char* PlayerTypeName = "Player";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpForceName = "JumpForce";
public:
    static BaseRTTI* CreatePlayerComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;    
public:
    //temp :sholud delete
    bool jumpPressed = false;
    int m_iMaxJumpCount = 1;
};