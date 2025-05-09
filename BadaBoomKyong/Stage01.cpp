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
	Serializer::GetInstance()->LoadJson_Object("json/temp/temp.json");
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::DEFAULT, GROUP_TYPE::TEMP);
}

void Stage01::Update()
{	
    auto in = InputManager::GetInstance();
	auto wb=GameObjectManager::GetInstance()->FindObject("WALL_BACK");
	Transform* trs=static_cast<Transform*>(wb->FindComponent(Transform::TransformTypeName));
	trs->AddRotationX(0.01f);
	/*trs->AddRotationY(0.01f);
	trs->AddRotationZ(0.01f);*/
}

void Stage01::Exit()
{	
	Serializer::GetInstance()->SaveJson_Object("json/temp/temp_3D.json",true);
	Serializer::GetInstance()->SaveJson_Object("json/temp/temp.json", false);
	GameObjectManager::GetInstance()->DeleteAllObject();
}