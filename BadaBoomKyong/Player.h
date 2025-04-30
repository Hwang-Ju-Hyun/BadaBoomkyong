#pragma once
#include "BaseComponent.h"
#include "ICollisionHandler.h"
#include <glm.hpp>

class Transform;
class Sprite;
class GameObject;
class Collider;
class RigidBody;

class Player :
    public BaseComponent
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
    float m_fSpeed=0.f;
    float m_fVerticalVelocity = 0.f;
    float m_fJumpForce = 0.f;    
    bool m_bIsGround = false;
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    inline void SetJumpForce(float _force) { m_fJumpForce = _force; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }

    inline float GetSpeed()const { return m_fSpeed; }
    inline float GetJumpForce()const { return m_fJumpForce; }
public:
    //virtual void EnterCollision(Collider* _other)override;
    //virtual void OnCollision(Collider* _other)   override;
    //virtual void ExitCollision(Collider* _other) override;    
public:
    bool JumpAble();
    void Jump();
    void Move();  
public:
    static constexpr const char* PlayerTypeName = "Player";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpForceName = "JumpForce";
public:
    static BaseRTTI* CreatePlayerComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;

};