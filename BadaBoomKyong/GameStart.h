#pragma once
#include "BaseLevel.h"

class UICanvas;
class UIButton;
class UIWidget;
class UIPanel;
class UIText;
class Camera;
class GameObject;

class GameStart :
    public BaseLevel
{
public:
	GameStart(STAGE_TYPE _stageType, const std::string& _name);	
	virtual ~GameStart() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
public:
	UIPanel* m_pUIBackground;
	UICanvas* m_pUICanvas;
	UICanvas* m_pUIBackCanvas;
	UIWidget* m_pUIWidget;
	UIButton* m_pUIStartBtn;
	UIButton* m_pUIEndBtn;	
	UIText* m_pStartText;
	UIText* m_pExitText;
};

