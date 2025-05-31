#pragma once
#include "BaseFactory.h"

class Melee;
class SoldierMelee;
class GameObject;

class MeleeFactory :
    public BaseFactory
{
public:
    MeleeFactory();
    virtual ~MeleeFactory()override;
public:
    virtual void Init()override;
    Melee* CreateMelee(GROUP_TYPE _type);
    virtual void Exit()override;
private:
    GameObject* m_pSoldierMeleeObject = nullptr;
    SoldierMelee*m_pSoldierMelee = nullptr;
public:
    static constexpr const char* MeleeFactoryTypeName = "MeleeFactory";
};

