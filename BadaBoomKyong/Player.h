#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class Transform;
class Sprite;
class GameObject;
class Collider;
class RigidBody;
class BulletFactory;
class Bullet;

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
private:
    BulletFactory* m_pBulletFactory=nullptr;
    Bullet* m_pBullet;
private:
    float m_fSpeed=0.f;
    float m_fVerticalVelocity = 0.f;        
    float m_fJumpImpulse = 500.f;
public:
    bool m_bIsGround = false;
    int m_iCurJumpCount = 0;
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    inline void SetIsGround(bool _ground) { m_bIsGround = _ground; }
    inline bool GetIsGround()const { return m_bIsGround; }
    //inline void SetJumpForce(float _force) { m_fJumpForce = _force; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }    

    inline float GetSpeed()const { return m_fSpeed; }
    //inline float GetJumpForce()const { return m_fJumpForce; }
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;    
public:
    //bool JumpAble();
    void Jump();
    void Move();  
    void Fire();
    //bool IsGround();
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