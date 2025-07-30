#pragma once
#include "Melee.h"

class Transform;
class Sprite;
class Collider;
class Player;
class Monster;

class PlayerMelee :
    public Melee
{
public:
    PlayerMelee(GameObject* _owner,GameObject* _shooter);
    virtual ~PlayerMelee()override;
private:
	Transform* m_pTransform=nullptr;
	Sprite* m_pSprite	   =nullptr;
	Collider* m_pCollider  =nullptr;
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
	Monster* m_pMonster = nullptr;
private:
	glm::vec3 m_vOffset;
public:
	virtual void Init()  override;
	virtual void Awake() override;
	virtual void Update()override;
	virtual void Exit()  override;
public:
	virtual void EnterCollision(Collider* _col)override;
	virtual void OnCollision(Collider* _col)override;
	virtual void ExitCollision(Collider* _col) override;
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static constexpr const char* PlayerMeleeTypeName = "PlayerMelee";
};

