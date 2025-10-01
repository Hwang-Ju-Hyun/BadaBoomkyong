#include "StageTest.h"
#include "CollisionManager.h"
#include "Serializer.h"

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

#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "FactoryManager.h"
#include "RenderManager.h"
#include "ComponentManager.h"
#include "GameObjectManager.h"

void StageTest::Exit()
{
	Serializer::GetInstance()->SaveJson_Object("json/Level/StageTest/StageTest_3D.json",true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/StageTest/StageTest_2D.json", false);
	ComponentManager::GetInstance()->Exit();

	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	GameObjectManager::GetInstance()->Exit();
	ResourceManager::GetInstance()->RemoveAllRes();
	ModelManager::GetInstance()->Exit();

	RenderManager::GetInstance()->Exit();
	EventManager::GetInstance()->Exit();

#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG
}
