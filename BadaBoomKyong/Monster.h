#pragma once
#include "MonoBehaviour.h"

class Transform;
class Sprite;
class GameObject;
class Collider;
class RigidBody;

class Monster :
    public MonoBehaviour
{
public:
    Monster(GameObject* _owner);
    virtual ~Monster()override;
private:
    Transform* m_pTransform = nullptr;
    Sprite* m_pSprite = nullptr;
    Collider* m_pCollider = nullptr;
    RigidBody* m_pRigidBody = nullptr;
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
private:
    float m_fSpeed = 0.f;
    float m_fVerticalVelocity = 0.f;
    float m_fJumpImpulse = 500.f;
    bool m_bIsGround = false;
public:
    inline void SetIsGround(bool _ground) { m_bIsGround = _ground; }
    inline bool GetIsGround()const { return m_bIsGround; }
    inline void SetSpeed(float _speed) { m_fSpeed = _speed; }
    inline float GetSpeed()const { return m_fSpeed; }
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;
public:
    static BaseRTTI* CreateMonsterComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
public:
    static constexpr const char* MonsterTypeName = "Monster";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpForceName = "JumpForce";
};

