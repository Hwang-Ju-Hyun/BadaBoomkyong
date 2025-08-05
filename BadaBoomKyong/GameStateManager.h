#pragma once
#include "Singleton.h"
#include <vector>
#include "header.h"

class BaseLevel;

class GameStateManager
{
public:
	SINGLETON(GameStateManager);
private:
	BaseLevel* m_pCurrentLevel=nullptr;
	BaseLevel* m_pPreviousLevel=nullptr;
	STAGE_TYPE m_eCurrentStageType;
public:
	void Init();
	void Update();
	void Exit();
public:
	void ChangeLevel(BaseLevel* _lvl);
	inline BaseLevel* GetCurrentLevel() { return m_pCurrentLevel; }
	inline const STAGE_TYPE GetStageType() const { return m_eCurrentStageType; }
};