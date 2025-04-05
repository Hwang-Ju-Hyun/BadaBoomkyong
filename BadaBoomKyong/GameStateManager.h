#pragma once
#include "Singleton.h"
#include <vector>

class BaseLevel;

class GameStateManager
{
public:
	SINGLETON(GameStateManager);
private:
	BaseLevel* m_pCurrentLevel=nullptr;
	BaseLevel* m_pPreviousLevel=nullptr;
public:
	void Init();
	void Update();
	void Exit();
public:
	void ChangeLevel(BaseLevel* _lvl);
	inline BaseLevel* GetCurrentLevel() { return m_pCurrentLevel; }
};