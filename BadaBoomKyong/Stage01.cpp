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

Stage01::Stage01(const std::string& _name)
	:BaseLevel(_name)
{
	lvl_2 = new Stage02("Stage02");
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage01/Stage01_3D.json");
	//Serializer::GetInstance()->LoadJson_Object("json/temp/temp.json");		

	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLATFORM);
}

static int a = 0;
void Stage01::Update()
{				
	
}

#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "FactoryManager.h"
#include "RenderManager.h"
void Stage01::Exit()
{	
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_3D.json",true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_2D.json", false);
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