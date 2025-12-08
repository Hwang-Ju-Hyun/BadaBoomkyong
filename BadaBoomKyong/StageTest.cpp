#include "StageTest.h"
#include "CollisionManager.h"
#include "Serializer.h"
#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "FactoryManager.h"
#include "RenderManager.h"
#include "ComponentManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "MainEditor.h"


StageTest::StageTest(STAGE_TYPE _stageType,const std::string& _name)
	:BaseLevel(_stageType,_name)
{
}

StageTest::~StageTest()
{
}

void StageTest::Init()
{
	Serializer::GetInstance()->LoadJson_Object("json/Level/StageTest/StageTest_3D.json");



	FactoryManager::GetInstance()->Init();

	ComponentManager::GetInstance()->Init();

	RenderManager::GetInstance()->Init();
	RenderManager::GetInstance()->InitDebugLineShader();
	//RenderManager::GetInstance()->Init();
	//RenderManager::GetInstance()->InitDebugLineShader();


#ifdef _DEBUG	
	MainEditor::GetInstance()->Init();
#endif
	UIManager::GetInstance()->Init();


	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);

}

void StageTest::Update()
{
}



void StageTest::Exit()
{
	//Serializer::GetInstance()->SaveJson_Object("json/Level/StageTest/StageTest_3D.json",true);
	//Serializer::GetInstance()->SaveJson_Object("json/Level/StageTest/StageTest_2D.json", false);
	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	EventManager::GetInstance()->Exit();
	UIManager::GetInstance()->Exit();
	GameObjectManager::GetInstance()->Exit();
	//ResourceManager::GetInstance()->RemoveAllRes();
	//ModelManager::GetInstance()->Exit();

	RenderManager::GetInstance()->Exit();

#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG
}
