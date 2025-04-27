#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

class Transform;
class Sprite;
class GameObject;
class Collider;

class Player :
    public BaseComponent
{
public:
    Player(GameObject* _owner);
    virtual ~Player()override;
private:
    Transform* m_pTransform = nullptr;
    Sprite* m_pSprite = nullptr;
    Collider* m_pCollider = nullptr;
private:
    float m_fSpeed=0.f;
    float m_fJumpScale = 0.f;    
public:
    virtual void Init()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    void Jump();
    void Move();  
public:
    static constexpr const char* PlayerTypeName = "Player";
    static constexpr const char* SpeedName = "Speed";
    static constexpr const char* JumpScaleName = "JumpScale";
public:
    static BaseRTTI* CreatePlayerComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
};