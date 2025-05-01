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
	Serializer::GetInstance()->LoadJson("json/temp/temp.json");	

	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::DEFAULT, GROUP_TYPE::TEMP);
}

void Stage01::Update()
{	
    auto in = InputManager::GetInstance();
	
}

void Stage01::Exit()
{	
	Serializer::GetInstance()->SaveJson("json/temp/temp.json");
	GameObjectManager::GetInstance()->DeleteAllObject();
}
