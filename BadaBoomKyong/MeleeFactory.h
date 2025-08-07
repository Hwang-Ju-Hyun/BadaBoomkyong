#pragma once
#include "BaseFactory.h"
#include <string>

class Melee;
class CurseDemonMelee;
class GameObject;
class PlayerMelee;
class ExecutionerDemon;
class ExecutionerDemonMelee;


class MeleeFactory :
    public BaseFactory
{
public:
    MeleeFactory(STAGE_TYPE _stage);
    virtual ~MeleeFactory()override;
public:
    virtual void Init()override;
    Melee* CreateMelee(GROUP_TYPE _type);
    Melee* CreateMelee(const std::string& _name);
    virtual void Exit()override;
private:
    GameObject* m_pCurseDemonMeleeObject = nullptr;
    CurseDemonMelee*m_pCurseDemonMelee = nullptr;
    
    GameObject* m_pPlayerMeleeObject = nullptr;
    PlayerMelee* m_pPlayerMelee = nullptr;

    GameObject* m_pExecutionerDemonMeleeObject = nullptr;
    ExecutionerDemonMelee* m_pExecutionerDemonMelee = nullptr;

private:
    virtual void InitStage01()  override;
    virtual void InitStage02()  override;
    virtual void InitStage03()  override;
    virtual void InitStageTest()override;
public:
    static constexpr const char* MeleeFactoryTypeName = "MeleeFactory";
};

