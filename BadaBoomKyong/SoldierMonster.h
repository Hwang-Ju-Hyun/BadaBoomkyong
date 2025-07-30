#pragma once
#include "Monster.h"
#include "ObjectPool.h"

class BulletFactory;
class SoldierGrenade;
class Bullet;
class Transform;
class GameObject;
class Melee;
class MeleeFactory;


class SoldierMonster :
    public Monster
{
public:
    SoldierMonster(GameObject* _owner);
    virtual ~SoldierMonster()override;        
//Range
private:    
    BulletFactory* m_pBulletFactory = nullptr;
    ObjectPool<SoldierGrenade, 30>* m_pGrenadePool = nullptr;
    Bullet* m_pBullet=nullptr;
private:
    //Melee Object
    GameObject* m_pMeleeObj = nullptr;
    Collider*  m_pMeleeCol = nullptr;
    Sprite* m_pMeleeSpr = nullptr;
    Transform* m_pMeleeTrs = nullptr;
    static constexpr const char* SoldierMonsterMeleeObjTypeName = "SoldierMonsterMeleeObject";
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
    float m_fDirection = 1.f;          //Postive : Right | Negative : Left 
public:
    inline void SetMoveDirection(int _dir) { m_iMoveDirection = _dir; }
    inline int GetMoveDirection()const { return m_iMoveDirection; }
    inline void SetDirection(float _dir) { m_fDirection = _dir; }
    inline float GetDirection()const { return m_fDirection; }
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
public:
    virtual void EnterCollision(Collider* _other)override;
    virtual void OnCollision(Collider* _other)   override;
    virtual void ExitCollision(Collider* _other) override;
public:
    static constexpr const char* SoldierMonsterTypeName = "SoldierMonster";      
    static constexpr const char* DetectRangeName = "DetectRange";
    static constexpr const char* RangedMoveAtkRangeName = "RangedMoveAtkRange";
    static constexpr const char* MeleeAtkRangeName = "MeleeAtkRange";
public:
    static BaseRTTI* CreateSoliderMonsterComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};