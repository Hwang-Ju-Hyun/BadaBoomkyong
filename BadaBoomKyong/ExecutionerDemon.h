#pragma once
#include "Monster.h"
#include "ObjectPool.h"

class BulletFactory;
class ExecutionerDemonFireBall;
class Bullet;
class Transform;
class GameObject;
class Melee;
class MeleeFactory;

class ExecutionerDemon :
    public Monster
{
public:
    ExecutionerDemon(GameObject* _owner);
    virtual ~ExecutionerDemon()override;
private:
    //Range
    BulletFactory* m_pBulletFactory = nullptr;
    ObjectPool<ExecutionerDemonFireBall, 30>* m_pFireBallPool = nullptr;
    Bullet* m_pBullet = nullptr;
private:
    //Melee Object
    GameObject* m_pMeleeObj = nullptr;
    Collider* m_pMeleeCol = nullptr;
    Sprite* m_pMeleeSpr = nullptr;
    Transform* m_pMeleeTrs = nullptr;
    static constexpr const char* ExecutionerDemonMeleeObjTypeName = "ExecutionerDemonMeleeObject";
public:
    inline BulletFactory* GetBulletFactory()const { return m_pBulletFactory; };
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
public:
    void Fire();
    void MeleeAttack();    
    MeleeFactory* m_pMeleeFactory = nullptr;
    Melee* m_pMelee = nullptr;
    bool m_bCanMeleeAttack = false;
    float m_fMeleeCoolTimeAcc = 0.f;
    bool m_bMeleeAtkDone = false;
public:
    void Patrol();
    float m_fAccPatrolDistance=0.f;
    bool m_bIsPatrolMoveDone = true;
    float m_fPatrolRandDistance = 0.f;
private:
    float m_fOffsetTimeAcc = 0.f;
    float m_fOffsetTime = 0.8f;
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;
public:
    static constexpr const char* ExecutionerDemonTypeName = "ExecutionerDemon";
    static constexpr const char* DetectRangeName = "DetectRange";
    static constexpr const char* RangedMoveAtkRangeName = "RangedMoveAtkRange";
    static constexpr const char* MeleeAtkRangeName = "MeleeAtkRange";
public:
    static BaseRTTI* CreateExecutionerDemonComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};

