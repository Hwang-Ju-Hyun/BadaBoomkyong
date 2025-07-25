#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>
#include <map>

class GameObject;
class TextureResource;

struct AnimationSpriteSheet
{
public:    
    std::string m_sAnimationName = "No Animation";    
    TextureResource* m_pTexture;
public:
    int m_iSheet_Max;
    int m_iSheet_Row;
    int m_iSheet_Col;
    float m_fSheet_UV_Width;
    float m_fSheet_UV_Height;
    float m_fSheet_UV_offset_X;
    float m_fSheet_UV_offset_Y;
public:
    float m_fDuration_per_frame = 0.f;
    bool m_bLoop = false; 
    int m_bLoopCount = 0;
};

class Animator :
    public BaseComponent
{
public:
    Animator(GameObject* _owner);
    ~Animator();
private:
    std::map<std::string, AnimationSpriteSheet*> m_mapAnimation;
    AnimationSpriteSheet* m_pCurrentAnimation = nullptr;
public:
    inline void SetAnimation(AnimationSpriteSheet* _anim) { m_pCurrentAnimation = _anim; }
    inline AnimationSpriteSheet* GetAnimation()const { return m_pCurrentAnimation; }
private:
    static float g_fAnmationAccTime;
    int m_iCurrentFrameIndex = 0;
public:
    virtual void Init()override;    
    virtual void Awake()override;
    virtual void Update()override;
    virtual void Exit()override;
private:
    int m_iFlipX = 1;
public:
    AnimationSpriteSheet* AddSpriteSheet(std::string _name, AnimationSpriteSheet* _clip);
    void ChangeAnimation(const std::string& _animName);
    inline const void TurnOnFlipX() { m_iFlipX *= -1; }
public:
    static BaseRTTI* CreateAnimatiorComponent();
    virtual void LoadFromJson(const json& _str)override;
    virtual json SaveToJson(const json& _str)override;    
public:
    static constexpr const char* AnimatorTypeName = "Animator";
    static constexpr const char* AnimationsTypeName = "Animations";
    static constexpr const char* AnimationNameTypeName = "Name";
    static constexpr const char* AnimationMaxTypeName = "Max";
    static constexpr const char* AnimationRowTypeName = "Row";
    static constexpr const char* AnimationColTypeName = "Col";
    static constexpr const char* AnimationTextureNameTypeName = "TextureName";
    static constexpr const char* AnimationTexturePathTypeName = "TexturePath";
    static constexpr const char* AnimationDurationTypeName = "Duration";
    static constexpr const char* AnimationLoopTypeName = "Loop";
public:
    virtual void EditInfoFromButton()override;
};