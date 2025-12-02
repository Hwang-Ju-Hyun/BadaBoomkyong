#pragma once
#include <vector>

class UIWidget;

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
private:
    UIWidget* m_pRoot;
    UIRenderSpace m_eRenderSpace;
public:
    std::vector<UIWidget*>m_vecChild;
    inline void AddChild(UIWidget* _child) { m_vecChild.push_back(_child); }
public:
    void Update(float _dt);
    void Render();
    void RenderScreenSpace();
    void RenderWorldSpace();
};
