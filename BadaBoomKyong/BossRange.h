#pragma once
#include "Bullet.h"

class Boss;
class ParticleSystem;
class RigidBody;

class BossRange :
    public Bullet
{
public:
	BossRange(GameObject* _owner, GameObject* _shooter);
	virtual ~BossRange()override;
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
	RigidBody* m_pRigidBody = nullptr;
	Boss* m_pBoss = nullptr;
	Transform* m_pBossTransform = nullptr;
private:
	float m_fThrowingForce = 0.f;
public:
	static constexpr const char* BossRangeTypeName = "BossRange";
	static constexpr const char* BossRangeImpulseTypeName = "BossRangeImpulse";
public:
	virtual void Fire() override;
	inline void SetCanFire(bool _able) { m_bCanFire = _able; }
	inline bool GetCanFire()const { return m_bCanFire; }
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static BaseRTTI* CreateBossRangeComponent();
public:
	bool m_bCanFire = false;
public:
	//CurseDemonBulletParticle* m_pCurseDemonBulletParticle;
	ParticleSystem* m_pPs;

	float m_fParticle_WaitAccTime;
	bool on = false;
	float m_fParticle_WaitingTime = 0.001f;
};

