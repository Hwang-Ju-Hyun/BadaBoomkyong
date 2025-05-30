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
class BulletFactory;

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
    AI* m_pAI = nullptr;
    Player* m_pPlayer;
    Transform* m_pPlayerTransform = nullptr;
private:    
    float m_fDirection=1.f;          //Postive : Right | Negative : Left
    glm::vec3 m_vPosition = {};
    glm::vec3 m_vPlayerPosition = {};
public:
    inline void SetDirection(float _dir) { m_fDirection = _dir; }
    inline float GetDirection()const { return m_fDirection; }
private:
    float m_fDetectRange =0.f;
    glm::vec3 m_vRangedMoveAtkRange = {};
    glm::vec3 m_vMeleeAtkRange = {};
public:
    inline float GetDetectRange()const { return m_fDetectRange; }
    inline glm::vec3 GetRangedMoveAtkRange()const {return m_vRangedMoveAtkRange;}
    inline glm::vec3 GetMeleeAtckRange()const { return m_vMeleeAtkRange; }
private:
    float m_fSpeed = 0.f;
    float m_fVerticalVelocity = 0.f;
    float m_fJumpImpulse = 500.f;
    bool m_bIsGround = false;
    BulletFactory* m_pBulletFactory = nullptr;
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
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
    bool m_bCol=false;
public:
    static BaseRTTI* CreateMonsterComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
public:
    static constexpr const char* MonsterTypeName = "Monster";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpForceName = "JumpForce";
    static constexpr const char* DetectRangeName = "DetectRange";
    static constexpr const char* RangedMoveAtkRangeName = "RangedMoveAtkRange";
    static constexpr const char* MeleeAtkRangeName = "MeleeAtkRange";
public:
    inline BulletFactory* GetBulletFactory()const {return m_pBulletFactory;};
};

