#pragma once
#include "Monster.h"
#include <vector> 
#include <list>
#include "ObjectPool.h"
#include "BehaviorTreeNode.h"
#include "Ray.h"
#include "LineLenderer.h"

class ParticleSystem;
class BTAgent;
class BulletFactory;
class Bullet;
class Transform;
class GameObject;
class Melee;
class MeleeFactory;
class BlackBoard;

class Boss :
    public Monster
{
public:
    bool temp = false;
public:
    Boss(GameObject* _owner);
    virtual ~Boss()override;
private:
    BulletFactory* m_pBulletFactory = nullptr;    
    Bullet* m_pBullet = nullptr;
    Bullet* m_pConeBullet = nullptr;
public:
    BTNode* m_pBT;   
    BTAgent* m_pBTAgent;
    BTNode* BuildBossBT();    
private:    
    LineLenderer m_LineLenderer;
    std::vector<Bullet*> m_vecCone;    
    inline std::vector<Bullet*> GetVecCone() { return m_vecCone; }
    Ray m_ray;
    RayCastHit m_rayHit;
    void HandleGroundCol();
    glm::vec3 m_vAimingTargetPos;
public:
    inline std::vector<Bullet*>& GetConeVec() { return m_vecCone; }
    void SetAimingTargetPos(const glm::vec3& _pos) { m_vAimingTargetPos = _pos; }
    const glm::vec3& GetAiminngTargetPos()const { return m_vAimingTargetPos; }
private:
    //Melee Object
    GameObject* m_pMeleeObj = nullptr;
    Collider* m_pMeleeCol = nullptr;
    Sprite* m_pMeleeSpr = nullptr;
    Transform* m_pMeleeTrs = nullptr;   
    float m_fAimingDist = 0.f;
public:
    void Aiming(glm::vec3 _targetPos);
    inline void SetAimingDistance(const float _dist) { m_fAimingDist = _dist; }
    inline float GetAimingDistance()const { return m_fAimingDist; }
    inline Ray GetRay() const { return m_ray; }
    inline BulletFactory* GetBulletFactory()const { return m_pBulletFactory; };
    void SpawnPawn();     
public:
    float m_fMoveX = 0.f;
private:    
    glm::vec3 m_vTargetPos;
  
    float m_fDetectRange = 0.f;
    glm::vec3 m_vRangedMoveAtkRange = {};
    glm::vec3 m_vMeleeAtkRange = {};
public:
    inline void SetTargetPos(const glm::vec3& _targetPos) { m_vTargetPos = _targetPos; }
    inline float GetDetectRange()const { return m_fDetectRange; }
    inline glm::vec3 GetRangedMoveAtkRange()const { return m_vRangedMoveAtkRange; }
    inline glm::vec3 GetMeleeAtckRange()const { return m_vMeleeAtkRange; }
private:
    //moveDirection은 스텝이 뒤로가고 앞으로가고이고
    //그냥 direction은 오른쪽을 바라보느냐 왼쪽을 바라보냐임
    int m_iMoveDirection = 1;            //Postive : Right | Negative : Left 
    float m_fJumpImpulse=1000.f;
public:
    inline void SetJumpImpulse(float _impulse) { m_fJumpImpulse = _impulse; }
    inline float GetJumpImpulse()const { return m_fJumpImpulse; }
public:
    inline void SetMoveDirection(int _dir) { m_iMoveDirection = _dir; }
    inline int GetMoveDirection()const { return m_iMoveDirection; }
    void Move();
    void Jump();    
    void TelePort(const glm::vec3& _target);
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    void Fire();
    void MeleeAttack();
    bool IsMeleeAnimDone();
    MeleeFactory* m_pMeleeFactory = nullptr;
    Melee* m_pMelee = nullptr;
    bool m_bCanMeleeAttack = false;
    float m_fMeleeCoolTimeAcc = 0.f;
    bool m_bMeleeAtkDone = false;
private:
    float m_fOffsetTimeAcc = 0.f;
    float m_fOffsetTime = 0.015f;
    bool m_bJumpMeleeAttacking=false;
    bool m_bIsNormalAttacking = false;
    bool m_bIsFalling = false;    
private:
    void StateHandle();
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;
public:
    static constexpr const char* BossMeleeObjTypeName = "BossMeleeObject";
    static constexpr const char* BossTypeName = "Boss";
    static constexpr const char* DetectRangeName = "DetectRange";
    static constexpr const char* RangedMoveAtkRangeName = "RangedMoveAtkRange";
    static constexpr const char* MeleeAtkRangeName = "MeleeAtkRange";
public:
    static BaseRTTI* CreateBossComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
    
};

