#pragma once
#include "Bullet.h"

class Transform;
class Sprite;
class RigidBody;
class ExecutionerDemon;

class ExecutionerDemonFireBall :
    public Bullet
{
public:
    ExecutionerDemonFireBall(GameObject* _owner, GameObject* _shooter);
    virtual ~ExecutionerDemonFireBall()override;
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
	Player* m_pPlayer = nullptr;
	Transform* m_pPlayerTransform = nullptr;
	ExecutionerDemon* m_pExecutionerDemon = nullptr;
	Transform* m_pExecutionerDemonTransform = nullptr;
	Transform* m_pTransform = nullptr;
	Sprite* m_pSprite = nullptr;
	Collider* m_pCollider = nullptr;
	RigidBody* m_pRigidBody = nullptr;
private:
	float m_fThrowingForce = 0.f;
public:
	static constexpr const char* ExecutionerDemonFireBallTypaName = "ExecutionerDemonFireBall";
	static constexpr const char* ExecutionerDemonFireBallImpulseTypeName = "ExecutionerDemonFireBallImpulse";
public:
	virtual void Fire() override;
	inline void SetCanFire(bool _able) { m_bCanFire = _able; }
	inline bool GetCanFire()const { return m_bCanFire; }
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static BaseRTTI* CreateThrowingWeaponComponent();
private:
	bool m_bCanFire = false;
};