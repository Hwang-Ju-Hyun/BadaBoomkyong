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
	GameObject* plane = new GameObject("Plane",MODEL_TYPE::PLANE,GROUP_TYPE::TEMP,true);
	Transform* plane_trs=static_cast<Transform*>(plane->AddComponent_and_Get(Transform::TransformTypeName, new Transform(plane)));	
	plane->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(plane));
	plane_trs->SetRotation({ 0.f,90.f,0.f });
	
	GameObject* cube= new GameObject("Cube", MODEL_TYPE::CUBE, GROUP_TYPE::TEMP,true);
	Transform* cube_trs=static_cast<Transform*>(cube->AddComponent_and_Get(Transform::TransformTypeName, new Transform(cube)));
	cube->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(cube));
	cube_trs->SetPosition({ 0,0,0 });
	cube_trs->SetScale({ 10.f,10.f,10.f });
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::DEFAULT, GROUP_TYPE::TEMP);
}

void Stage01::Update()
{	
    auto in = InputManager::GetInstance();
	
}

void Stage01::Exit()
{	
	//Serializer::GetInstance()->SaveJson("json/temp/temp.json");
	GameObjectManager::GetInstance()->DeleteAllObject();
}
