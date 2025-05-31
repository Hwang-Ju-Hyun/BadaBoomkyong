#pragma once
#include "Melee.h"

class Transform;
class Sprite;
class SoldierMelee;
class SoldierMonster;

class SoldierMelee :
    public Melee
{
public:
    SoldierMelee(GameObject* _owner);
    virtual ~SoldierMelee()override;
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
	SoldierMelee* m_pSoldierMelee = nullptr;
	SoldierMonster* m_pSoldierMonster = nullptr;	
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static constexpr const char* SoldierMeleeTypeName = "SoldierMelee";
};

