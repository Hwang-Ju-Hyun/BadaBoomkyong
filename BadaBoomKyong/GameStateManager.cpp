#include "GameStateManager.h"
#include "BaseLevel.h"
#include <cassert>

GameStateManager::GameStateManager(){}

GameStateManager::~GameStateManager(){}

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

void GameStateManager::ChangeLevel(BaseLevel* _lvl)
{
	if (_lvl == nullptr)
	{
		Exit();
		delete m_pCurrentLevel;
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