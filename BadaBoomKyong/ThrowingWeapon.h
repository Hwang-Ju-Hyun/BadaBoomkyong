#pragma once
#include "Bullet.h"

class Transform;
class Sprite;
class RigidBody;

class ThrowingWeapon :
	public Bullet
{
public:
    ThrowingWeapon(GameObject* _owner);
    virtual ~ThrowingWeapon()override;
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
private:
	float m_fThrowingForce = 0.f;
public:
	static constexpr const char* ThrowingWeaponTypeName = "ThrowingWeapon";
	static constexpr const char* ThrowingImpulseTypeName = "ThrowingImpulse";
public:
	virtual void LoadFromJson(const json& _str) override;
	virtual json SaveToJson(const json& _str) override;
public:
	static BaseRTTI* CreateThrowingWeaponComponent();

	//todo: °íÄ¡¼À
	void Throw();
	inline void SetThrowable(bool _able) { m_bThrowable = _able; }
	inline bool GetThrowable()const { return m_bThrowable; }
private:
	bool m_bThrowable=false;
};

