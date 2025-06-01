#pragma once
#include "Bullet.h"

class Player;

class Pistol :
    public Bullet
{
public:
    Pistol(GameObject* _owner,GameObject* _shooter);
    virtual ~Pistol()override;
public:
    virtual void Init()  override;
    virtual void Awake() override;
    virtual void Update()override;
    virtual void Exit()  override;
public:
    virtual void Fire()override;
private:
    Transform* m_pTransform = nullptr;
    Sprite* m_pSprite = nullptr;
    Collider* m_pCollider = nullptr;
private:
    Player* m_pPlayer = nullptr;
    Transform* m_pPlayerTrs = nullptr;
private:
    float m_fSpeed = 0.f;
public:
    virtual void EnterCollision(Collider* _col)override;
    virtual void OnCollision(Collider* _col)override;
    virtual void ExitCollision(Collider* _col) override;
public:
    virtual void LoadFromJson(const json& _str) override {};
    virtual json SaveToJson(const json& _str) override { return nullptr; };
    static BaseRTTI* CreatePistolComponent();
    static constexpr const char* PistolTypeName = "Pistol";
};

