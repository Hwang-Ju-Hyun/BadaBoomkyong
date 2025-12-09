#include "GameStateManager.h"
#include "BaseLevel.h"
#include <cassert>
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "StageTest.h"
#include "GameStart.h"
#include "GameOver.h"
#include "Congratulation.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "ObjectPoolManager.h"
#include "FactoryManager.h"
#include "ModelManager.h"
#include "ResourceManager.h"
#include "Window.h"
#include "UIManager.h"
#include "RenderManager.h"
#include "AudioManager.h"


GameStateManager::GameStateManager()
{
	m_hashLevels.insert({ STAGE_TYPE::GAME_START,new GameStart(STAGE_TYPE::GAME_START,"GameStart") });
	m_hashLevels.insert({ STAGE_TYPE::STAGE_01,new Stage01(STAGE_TYPE::STAGE_01,"Stage01") });
	m_hashLevels.insert({ STAGE_TYPE::STAGE_02,new Stage02(STAGE_TYPE::STAGE_02,"Stage02") });
	//m_hashLevels.insert({ STAGE_TYPE::STAGE_03,new Stage03(STAGE_TYPE::STAGE_03,"Stage03") });
	m_hashLevels.insert({ STAGE_TYPE::STAGE_TEST,new StageTest(STAGE_TYPE::STAGE_TEST,"StageTest") });
	m_hashLevels.insert({ STAGE_TYPE::GAME_OVER,new GameOver(STAGE_TYPE::GAME_OVER,"GameOver") });
	//m_hashLevels.insert({ STAGE_TYPE::GAME_OVER,new GameOver(STAGE_TYPE::GAME_OVER,"GameOver")});
	//m_hashLevels.insert({ STAGE_TYPE::CONGRATULATION,new Congratulation(STAGE_TYPE::CONGRATULATION,"Congratulation") });
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
	if(m_pCurrentLevel)
		m_pCurrentLevel->Update();
}

void GameStateManager::Exit()
{
	if (m_pCurrentLevel != nullptr)
	{
		m_pCurrentLevel->Exit();
		m_pCurrentLevel = nullptr;
	}	
}

void GameStateManager::DeleteAll()
{	
	GameObjectManager::GetInstance()->Exit();
	ComponentManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();
	FactoryManager::GetInstance()->Exit();
	ModelManager::GetInstance()->Exit();
	UIManager::GetInstance()->Exit();
	ResourceManager::GetInstance()->RemoveAllRes();
	RenderManager::GetInstance()->Exit();
	AudioManager::GetInstance()->Exit();
	Window::GetInstance()->Exit();
	//#ifdef _DEBUG
	//    // Cleanup
	//    ImGui_ImplOpenGL3_Shutdown();
	//    ImGui_ImplGlfw_Shutdown();
	//    ImGui::DestroyContext();
	//#endif // DEBUG	
	glfwTerminate();
}

void GameStateManager::DeleteAllStages()
{
	for (auto iter = m_hashLevels.begin();iter != m_hashLevels.end();iter++)
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}
#include "Application.h"
void GameStateManager::ChangeLevel(BaseLevel* _lvl)
{
	if (_lvl == nullptr)
	{
		Exit();
		if (m_pPreviousLevel)
		{
			delete m_pPreviousLevel;
			m_pPreviousLevel = nullptr;
		}
			
		DeleteAllStages();			
		glfwSetWindowShouldClose(Window::GetInstance()->GetWindowHandle(), true);
		return;
	}
	if (_lvl)
		m_eLastStageType= _lvl->GetStageType();

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

void GameStateManager::RestartLastStage()
{
	Exit();
	DeleteAllStages();
	BaseLevel* newStage = nullptr;
	switch (m_eLastStageType)
	{
	case STAGE_TYPE::STAGE_01:
		newStage = new Stage01(STAGE_TYPE::STAGE_01, "Stage01");
		break;
	case STAGE_TYPE::STAGE_02:
		newStage = new Stage02(STAGE_TYPE::STAGE_02, "Stage02");
		break;
	case STAGE_TYPE::STAGE_TEST:		
		newStage = new StageTest(STAGE_TYPE::STAGE_TEST, "StageTest");
		break;
	}
	m_pCurrentLevel = newStage;
	m_hashLevels[m_eLastStageType] = newStage;

	m_pCurrentLevel->Init();
}
