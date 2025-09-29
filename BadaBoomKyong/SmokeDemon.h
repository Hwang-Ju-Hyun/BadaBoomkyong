#pragma once
#include "Monster.h"

class Melee;
class MeleeFactory;
class AI;
class ParticleSystem;
class SmokeAttackParticle;

class SmokeDemon :
    public Monster
{
public:
    bool smoking = false;
    SmokeDemon(GameObject* _owner);
    virtual ~SmokeDemon()override;
public:
    void MeleeAttack();
    MeleeFactory* m_pMeleeFactory = nullptr;
    Melee* m_pMelee = nullptr;
    bool m_bCanMeleeAttack = false;
    float m_fMeleeCoolTimeAcc = 0.f;
    bool m_bMeleeAtkDone = false;
public:
    void Patrol();
    float m_fAccPatrolDistance = 0.f;
    bool m_bIsPatrolMoveDone = true;
    float m_fPatrolRandDistance = 0.f;
public:
    SmokeAttackParticle* m_pSmokeAttackParticle;
    ParticleSystem* m_pPs;
private:
    float m_fDetectRange = 0.f;
    glm::vec3 m_vRangedMoveAtkRange = {};
    glm::vec3 m_vMeleeAtkRange = {};
public:
    inline float GetDetectRange()const { return m_fDetectRange; }
    inline glm::vec3 GetRangedMoveAtkRange()const { return m_vRangedMoveAtkRange; }
    inline glm::vec3 GetMeleeAtckRange()const { return m_vMeleeAtkRange; }
private:
    //moveDirection은 스텝이 뒤로가고 앞으로가고이고
    //그냥 direction은 오른쪽을 바라보느냐 왼쪽을 바라보냐임
    int m_iMoveDirection = 1;            //Postive : Right | Negative : Left    
public:
    inline void SetMoveDirection(int _dir) { m_iMoveDirection = _dir; }
    inline int GetMoveDirection()const { return m_iMoveDirection; }
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
private:
    float m_fOffsetTimeAcc = 0.f;
    float m_fOffsetTime = 1.8f;
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;
public:
    static constexpr const char* SmokeDemonTypeName = "SmokeDemon";
    static constexpr const char* DetectRangeName = "DetectRange";
    static constexpr const char* RangedMoveAtkRangeName = "RangedMoveAtkRange";
    static constexpr const char* MeleeAtkRangeName = "MeleeAtkRange";
public:
    static BaseRTTI* CreateSmokeDemonComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;

public:
    float m_fMeleeStateChange_OffsetAccTime = 0.f;
    float m_fMeleeStateChange_OffsetTime = 2.0f;
    float m_fSmokeParticle_WaitAccTime = 0.f;
    float m_fSmokeParticle_WaitingTime = 0.7f;
};

