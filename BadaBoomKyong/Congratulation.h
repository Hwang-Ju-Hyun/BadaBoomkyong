#pragma once
#include "BaseLevel.h"


class UICanvas;
class UIButton;
class UIWidget;
class UIPanel;
class UIText;
class Camera;
class GameObject;

class Congratulation :
    public BaseLevel
{
public:
	Congratulation(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~Congratulation() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;

	UICanvas* m_pUIBackCanvas = nullptr;
	UIPanel* m_pUIBackground = nullptr;
	UIText* m_pConText = nullptr;	
	UIText* m_pExitText = nullptr;
};

