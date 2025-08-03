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

    // 복사 생성자: 깊은 복사(단, 텍스처는 공유해도 괜찮음)
    AnimationSpriteSheet(const AnimationSpriteSheet& other)
    {
        m_sAnimationName = other.m_sAnimationName;
        m_pTexture = other.m_pTexture; // 텍스처는 공유해도 됨
        m_iSheet_Max = other.m_iSheet_Max;
        m_iSheet_Row = other.m_iSheet_Row;
        m_iSheet_Col = other.m_iSheet_Col;
        m_fDuration_per_frame = other.m_fDuration_per_frame;
        m_bLoop = other.m_bLoop;
        m_bLoopCount = other.m_bLoopCount;
        m_fSheet_UV_Width = other.m_fSheet_UV_Width;
        m_fSheet_UV_Height = other.m_fSheet_UV_Height;
        m_fSheet_UV_offset_X = other.m_fSheet_UV_offset_X;
        m_fSheet_UV_offset_Y = other.m_fSheet_UV_offset_Y;
    }

    AnimationSpriteSheet() = default;
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
#ifdef _DEBUG
public:
    virtual void EditInfoFromButton()override;
#endif
public:
    float m_fAnmationAccTime = 0.f;
};