#pragma once
#include "BaseState.h"
#include "ThrowingWeapon.h"
#include "ObjectPool.h"

class ThrowingWeapon;

class RangedState :
    public BaseState
{
public:
    RangedState(MONSTER_STATE _state=MONSTER_STATE::RANGE_ATTACK_STATE);
    virtual ~RangedState()override;
public:
    virtual void Init()  override;
    virtual void Update()override;
    virtual void Exit()  override;    
public:
    //todo Áö¿ì¼À
    void MoveSideBySide();
    void ThrowAttack();
    float m_fStepSum = 0.f;
    ThrowingWeapon* throwWeapon_comp=nullptr;
private:    
    ObjectPool<ThrowingWeapon, 30>*  m_pThrowWeaponPool = nullptr;
};

