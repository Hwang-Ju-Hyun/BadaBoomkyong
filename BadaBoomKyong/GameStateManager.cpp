#include "GameStateManager.h"
#include "BaseLevel.h"
#include <cassert>
#include "Stage01.h"
#include "Stage02.h"
#include "StageTest.h"

GameStateManager::GameStateManager()
{
	m_hashLevels.insert({ STAGE_TYPE::STAGE_01,new Stage01(STAGE_TYPE::STAGE_01,"Stage01") });
	m_hashLevels.insert({ STAGE_TYPE::STAGE_02,new Stage02(STAGE_TYPE::STAGE_02,"Stage02") });

	m_hashLevels.insert({ STAGE_TYPE::STAGE_TEST,new StageTest(STAGE_TYPE::STAGE_TEST,"StageTest") });
}

GameStateManager::~GameStateManager()
{	
}

void GameStateManager::Init()
{
	assert(m_pCurrentLevel != nullptr);	
	m_pCurrentLevel->Init();
}

void GameStateManager::Update()
{
	assert(m_pCurrentLevel != nullptr);
	m_pCurrentLevel->Update();
}

void GameStateManager::Exit()
{
	assert(m_pCurrentLevel != nullptr);
	m_pCurrentLevel->Exit();	
}

void GameStateManager::DeleteAll()
{
	for (auto iter = m_hashLevels.begin();iter != m_hashLevels.end();iter++)
	{
		delete iter->second;
		iter->second = nullptr;
	}
}

void GameStateManager::ChangeLevel(BaseLevel* _lvl)
{
	if (_lvl == nullptr)
	{
		Exit();
		if (m_pPreviousLevel)
			delete m_pPreviousLevel;
		DeleteAll();
		return;
	}
	if (m_pPreviousLevel)
	{
		delete m_pPreviousLevel;
		m_pPreviousLevel = nullptr;
	}
	if (m_pCurrentLevel)
	{
		Exit();
		m_pPreviousLevel = m_pCurrentLevel;
	}
	m_pCurrentLevel = _lvl;
	m_eCurrentStageType = _lvl->GetStageType();
	m_pCurrentLevel->Init();
}
