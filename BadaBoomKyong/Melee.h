#pragma once
#include "MonoBehaviour.h"
#include <glm.hpp>

class Melee :
    public MonoBehaviour
{
public:
    Melee(GameObject* _owner, GameObject* _attacker = nullptr);
    virtual ~Melee()override;
public:
    float m_fLifeTime = 0.f;
    inline void SetLifeTime(float _time) { m_fLifeTime = _time; }
    inline float GetLifetTime()const { return m_fLifeTime; }
    float m_fCurTime = 0.f;
private:
    GameObject* m_pAttacker = nullptr;
public:
    inline void SetAttacker(GameObject* _attakcer) { m_pAttacker = _attakcer; }
    inline GameObject* GetAttacker()const { return m_pAttacker; }
public:
    bool m_bCanMeleeAttack = false;  
public:
    virtual void LoadFromJson(const json& _str) override {};
    virtual json SaveToJson(const json& _str) override { return nullptr; };
    static BaseRTTI* CreateMeleeComponent();
    static constexpr const char* MeleeTypeName = "Melee";
};