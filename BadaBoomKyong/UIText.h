#pragma once
#include "UIWidget.h"
#include <string>

class UICanvas;

class UIText :
    public UIWidget
{
public:
    UIText(UICanvas* owner,
        const std::string& text,
        float x, float y,
        float scale,
        glm::vec3 color);

    virtual ~UIText()override {}

    void SetText(const std::string& t) { m_Text = t; }
    void SetColor(const glm::vec3& c) { m_Color = c; }
    void SetScale(float s) { m_Scale = s; }

    virtual void RenderScreenSpace() override;
    virtual void RenderWorldSpace(const Camera* cam) override {}

private:
    std::string m_Text;
    float m_Scale;
    glm::vec3 m_Color;
};

