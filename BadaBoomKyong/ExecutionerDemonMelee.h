#pragma once
#include "Melee.h"


class Transform;
class Sprite;
class ExecutionerDemonMelee;
class ExecutionerDemon;
class Player;


class ExecutionerDemonMelee :
    public Melee
{
public:
    ExecutionerDemonMelee(GameObject* _owner, GameObject* _attacker = nullptr);
    virtual ~ExecutionerDemonMelee()override;
public:
	virtual void Init()  override;
	virtual void Awake() override;
	virtual void Update()override;
	virtual void Exit()  override;
public:
	virtual void EnterCollision(Collider* _col)override;
	virtual void OnCollision(Collider* _col)override;
	virtual void ExitCollision(Collider* _col) override;
private:
	Transform* m_pTransform = nullptr;
	Sprite* m_pSprite = nullptr;
	Collider* m_pCollider = nullptr;
	ExecutionerDemonMelee* m_pExecutionerDemonMelee = nullptr;
	ExecutionerDemon* m_pExecutionerDemon = nullptr;
private:
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static constexpr const char* ExecutionerDemonMeleeTypeName = "ExecutionerDemonMelee";

};

