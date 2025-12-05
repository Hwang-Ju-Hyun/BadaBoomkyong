#pragma once
#include <vector>
#include <glm.hpp>

class UIButton;
class UIWidget;
class Camera;

enum class UIRenderSpace
{
    SCREEN_SPACE,
    WORLD_SPACE
};

class UICanvas   
{
public:
    UICanvas(UIRenderSpace _space);
    virtual ~UICanvas();
public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Camera* m_pCam;
public:
    int m_iUiTransform_location;
    int m_iUiShaderViewProj_location;
    int m_vUiShaderTransform;
    int m_iUiShaderColor_location;
    int m_iUiShaderMVP;    
    int m_iUiHas_texture_location;
    int m_iUiOut_texture_location;
    int m_iUV_Offset_Location;
    int m_iUV_Scale_Location;
    UIWidget* m_pRoot;
    UIRenderSpace m_eRenderSpace;

public:
    std::vector<UIWidget*>m_vecChild;
    inline void AddChild(UIWidget* _child) { m_vecChild.push_back(_child); }
public:
    void Init();
    void Update(float _dt);
    void Render();     
    void Exit();
    
    friend class UIWidget;
    friend class UIButton;
};
