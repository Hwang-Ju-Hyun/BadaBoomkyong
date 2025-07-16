#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>
#include <map>

class GameObject;

struct AnimationFrame
{
public:
    std::string m_sTextureName="No Frame";
    float m_fDuration=0.1f;    
};

struct AnimationClip
{
public:
    std::string m_sAnimationName = "No Animation";
    std::vector<AnimationFrame> m_vAnimationFrame;
    bool m_bLoop = false;    
};

class Animator :
    public BaseComponent
{
public:
    Animator(GameObject* _owner);
    ~Animator();
private:
    std::map<std::string, AnimationClip*> m_mapAnimation;
    AnimationClip* m_pCurrentAnimationClip = nullptr;
private:
    float m_fCurrentTime = 0.f;
    int m_fCurrentFrameIndex = 0;
public:
    virtual void Init()override;    
    virtual void Awake()override;
    virtual void Update()override;
    virtual void Exit()override;
public:
    inline void AddClip(std::string _name, AnimationClip* _clip) { m_mapAnimation.insert(std::make_pair(_name, _clip)); }
    void ChangeAnimation();
public:
    static BaseRTTI* CreateAnimatiorComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;
public:
    static constexpr const char* AnimatorTypeName = "Animation";
};