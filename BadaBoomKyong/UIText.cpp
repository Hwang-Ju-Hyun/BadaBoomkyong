#include "UIText.h"
#include "TextManager.h"
#include "UICanvas.h"

UIText::UIText(UICanvas* _owner,const std::string& text, float x, float y, float scale, glm::vec3 color)
	: UIWidget(_owner,x, y, 0.f, 0.f,0.f) // 텍스트는 width/height가 필요 없을 수 있음
    , m_Text(text)
    , m_Scale(scale)
    , m_Color(color)
{
}

void UIText::RenderScreenSpace()
{
    float absX = GetAbsoluteX();
    float absY = GetAbsoluteY();

    GetOwner()->AddText(m_Text,absX,absY,m_Scale,m_Color);
}
