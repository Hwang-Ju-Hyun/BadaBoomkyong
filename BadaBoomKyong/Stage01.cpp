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
	GameObject* temp = GameObjectManager::GetInstance()->FindObject("temp");
	GameObject* rec=GameObjectManager::GetInstance()->FindObject("rec");
	//tri->AddComponent_and_Get(Collider::ColliderTypeName, new Collider(tri));
	Collider* temp_col = dynamic_cast<Collider*>(temp->FindComponent(Collider::ColliderTypeName));
	Collider* rec_col = dynamic_cast<Collider*>(rec->FindComponent(Collider::ColliderTypeName));

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
