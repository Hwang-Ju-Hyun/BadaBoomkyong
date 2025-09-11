#include "Stage02.h"
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
#include "ModelManager.h"
#include "FactoryManager.h"
#include "MainEditor.h"
#include "RenderManager.h"
#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "Stage03.h"
#include "GameStateManager.h"

Stage02::Stage02(STAGE_TYPE _stageType,const std::string& _name)
	:BaseLevel(_stageType,_name)
{
	//lvl_3 = new Stage03(STAGE_TYPE::STAGE_03,"Stage03");
}

Stage02::~Stage02()
{
}

void Stage02::Init()
{	
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage02/Stage02_3D.json");		
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	//FactoryManager::GetInstance()->Init();
	//
	////ComponentInit
	//ComponentManager::GetInstance()->Init();
	//
	////RenderInit            
	//RenderManager::GetInstance()->Init();
	//RenderManager::GetInstance()->InitDebugLineShader();


#ifdef _DEBUG
	//MainEditor
	//MainEditor::GetInstance()->Init();
#endif
}

void Stage02::Update()
{
	
}

void Stage02::Exit()
{
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_3D.json", true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_2D.json", false);
	
	ComponentManager::GetInstance()->Exit();

	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	GameObjectManager::GetInstance()->Exit();

	ResourceManager::GetInstance()->RemoveAllRes();
	//ModelManager::GetInstance()->Exit();

	RenderManager::GetInstance()->Exit();
	EventManager::GetInstance()->Exit();

#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG	
}