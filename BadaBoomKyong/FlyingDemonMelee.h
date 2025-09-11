#pragma once
#include "Melee.h"


class Transform;
class Sprite;
class FlyingDemon;
class Player;

class FlyingDemonMelee :
    public Melee
{
public:
	FlyingDemonMelee(GameObject* _owner, GameObject* _attacker = nullptr);
	virtual ~FlyingDemonMelee()override;
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
	FlyingDemonMelee* m_FlyingDemonMelee = nullptr;
	FlyingDemon* m_pFlyingDemon = nullptr;
private:
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static constexpr const char* FlyingDemonMeleeTypeName = "FlyingDemonMelee";

};

