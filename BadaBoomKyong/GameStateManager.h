#pragma once
#include "Singleton.h"
#include <vector>
#include "header.h"
#include <unordered_map>

class BaseLevel;

class GameStateManager
{
public:
	SINGLETON(GameStateManager);
private:
	BaseLevel* m_pCurrentLevel=nullptr;
	BaseLevel* m_pPreviousLevel=nullptr;
	STAGE_TYPE m_eCurrentStageType;
	std::unordered_map<STAGE_TYPE, BaseLevel*> m_hashLevels;
public:
	void Init();
	void Update();
	void Exit();
	void DeleteAll();
public:
	void ChangeLevel(BaseLevel* _lvl);
	inline BaseLevel* FindLevel(STAGE_TYPE _eType){ return m_hashLevels[_eType]; }
	inline BaseLevel* GetCurrentLevel() { return m_pCurrentLevel; }
	inline const STAGE_TYPE GetStageType() const { return m_eCurrentStageType; }
};