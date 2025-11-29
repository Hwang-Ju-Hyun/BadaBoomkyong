#pragma once
#include "Bullet.h"
#include "glm.hpp"
#include <gtx/quaternion.hpp>

class Player;
class Boss;
class ParticleSystem;
class RigidBody;

enum class ConeState
{
	RANDOM_ROTATE,
	AIMING,
	FIRE
};

class ConeRange :
	public Bullet
{
public:
	bool temp = false;
public:
	ConeRange(GameObject* _owner, GameObject* _shooter);
	virtual ~ConeRange()override;
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
	ConeState m_eState;
	Player* m_pPlayer;
	Transform* m_pPlayerTransform;
	Transform* m_pTransform = nullptr;
	Sprite* m_pSprite = nullptr;
	Collider* m_pCollider = nullptr;
	RigidBody* m_pRigidBody = nullptr;
	Boss* m_pBoss = nullptr;
	Transform* m_pBossTransform = nullptr;
private:
	float m_fThrowingForce = 0.f;
	bool m_bIsAiming = false;
	glm::quat target_rot = {};
	glm::vec3 m_vTarget_pos = {};
public:
	static constexpr const char* ConeRangeTypeName = "ConeRange";
	static constexpr const char* ConeRangeImpulseTypeName = "ConeRangeImpulse";
public:
	virtual void Fire() override;
	inline void SetCanFire(bool _able) { m_bCanFire = _able; }
	inline bool GetCanFire()const { return m_bCanFire; }
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
	static BaseRTTI* CreateConeRangeComponent();
public:
	bool m_bCanFire = false;
	float m_fSpeed = 5.f;
public:
	////CurseDemonBulletParticle* m_pCurseDemonBulletParticle;
	//ParticleSystem* m_pPs;
	//EnergyRayParticle* m_pEnergyRayParticle;
	//float m_fParticle_WaitAccTime;
	//bool on = false;
	//float m_fParticle_WaitingTime = 0.01f;
private:
	float m_fRotElapsedTime = 0.f;
	float m_fStopRotElapseTime = 0.f;
	float m_fAimingElapseTime = 0.f;
	float m_fAiming_MaxTime = 3.f;
	float m_fStopRotElapse_MaxTime = 5.f;
	glm::vec3 m_vBaseAxis;
	float m_fSeed;
};