#pragma once
#include "MonoBehaviour.h"

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
	void Init();
	void Update();
	void Exit();
private:
	Transform* m_pTransform=nullptr;
	Sprite* m_pSprite=nullptr;
	Collider* m_pCollider = nullptr;
public:
	virtual void EnterCollision(Collider* _col)override;
	virtual void OnCollision(Collider* _col)override;
	virtual void ExitCollision(Collider* _col) override;
private:
	float m_fSpeed = 0.f;
public:
	static constexpr const char* BulletTypeName = "Bullet";
public:
	virtual void LoadFromJson(const json& _str) {};
	virtual json SaveToJson(const json& _str) { return nullptr; };
public:
	static BaseRTTI* CreateBulletComponent();

	
//todo : ∏Æ∆Â≈‰∏µ «œº¿
public:
	bool m_bIsActive = false;
	bool reset() { m_bIsActive = false;}
};