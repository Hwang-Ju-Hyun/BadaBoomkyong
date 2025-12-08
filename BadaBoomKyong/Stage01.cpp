#include "Stage01.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "Serializer.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Transform.h"
#include "Player.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "RigidBody.h"
#include <iostream>
#include "Stage02.h"
#include "GameStateManager.h"
#include "RenderManager.h"
#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "FactoryManager.h"
#include "RenderManager.h"
#include "MainEditor.h"
#include "UIManager.h"

Stage01::Stage01(STAGE_TYPE _stageType, const std::string& _name)
	:BaseLevel(_stageType,_name)
{
	//lvl_2 = new Stage02(STAGE_TYPE::STAGE_02,"Stage02");
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{			
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage01/Stage01_3D.json");	

	FactoryManager::GetInstance()->Init();

	ComponentManager::GetInstance()->Init();

	RenderManager::GetInstance()->Init();
	RenderManager::GetInstance()->InitDebugLineShader();


#ifdef _DEBUG	
	MainEditor::GetInstance()->Init();
#endif
	UIManager::GetInstance()->Init();
	//todo : stage01으로 시작할꺼면 stage02 이거끄셈 그리고 이거 키고
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
}

void Stage01::Update()
{				
	
}


void Stage01::Exit()
{	
	//Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_3D.json",true);
	//Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_2D.json", false);
	
	//ComponentManager::GetInstance()->Exit();
	
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