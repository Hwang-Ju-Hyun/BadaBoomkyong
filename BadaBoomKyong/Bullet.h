#pragma once
#include "MonoBehaviour.h"

class Player;
class Transform;
class Sprite;
class Collider;

class Bullet
	:public MonoBehaviour
{
public:	
	Bullet(GameObject* _owner);	
	virtual ~Bullet()override;
public:
	virtual void Init()  override;
	virtual void Awake() override;
	virtual void Update()override;
	virtual void Exit()  override;
private:
	Transform* m_pTransform=nullptr;
	Sprite* m_pSprite=nullptr;
	Collider* m_pCollider = nullptr;
public:
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTrs = nullptr;
public:
	virtual void EnterCollision(Collider* _col)override;
	virtual void OnCollision(Collider* _col)override;
	virtual void ExitCollision(Collider* _col) override;
private:
	float m_fSpeed = 0.f;
public:
	static constexpr const char* BulletTypeName = "Bullet";
	
public:
	virtual void LoadFromJson(const json& _str) override{};
	virtual json SaveToJson(const json& _str) override{ return nullptr; };	
public:
	static BaseRTTI* CreateBulletComponent();	
};