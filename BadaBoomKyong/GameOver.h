#pragma once
#include "BaseLevel.h"

class UICanvas;
class UIWidget;
class UIPanel;
class UIText;

class GameOver :
    public BaseLevel
{
public:
	GameOver(STAGE_TYPE _stageType, const std::string& _name);
	virtual ~GameOver() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;

	UICanvas* m_pUIBackCanvas=nullptr;
	UIPanel* m_pUIBackground = nullptr;
	UIText* m_pGameOverText= nullptr;
	UIText* m_pReStartText=nullptr;
	UIText* m_pExitText= nullptr;
};