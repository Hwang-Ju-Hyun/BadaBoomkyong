#pragma once
#include "Melee.h"

class Transform;
class Sprite;
class CurseDemonMelee;
class CurseDemon;
class Player;

class CurseDemonMelee :
    public Melee
{
public:
    CurseDemonMelee(GameObject* _owner,GameObject* _attacker=nullptr);
    virtual ~CurseDemonMelee()override;
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
	CurseDemonMelee* m_pCurseDemonMelee = nullptr;
	CurseDemon* m_pCurseDemon = nullptr;
private:
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static constexpr const char* CurseDemonMeleeTypeName = "CurseDemonMelee";
};

