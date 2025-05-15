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

Stage01::Stage01(const std::string& _name)
	:BaseLevel(_name)
{
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{
	Serializer::GetInstance()->LoadJson_Object("json/temp/temp_3D.json");
	//Serializer::GetInstance()->LoadJson_Object("json/temp/temp.json");
	
	//Collider* Plat_col = static_cast<Collider*>(Plat->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(Plat)));

	

	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::DEFAULT, GROUP_TYPE::TEMP);
}

void Stage01::Update()
{						
}

void Stage01::Exit()
{	
	Serializer::GetInstance()->SaveJson_Object("json/temp/temp_3D.json",true);
	Serializer::GetInstance()->SaveJson_Object("json/temp/temp.json", false);
	ComponentManager::GetInstance()->Exit();
	GameObjectManager::GetInstance()->DeleteAllObject();
}