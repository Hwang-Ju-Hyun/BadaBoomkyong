#include "Stage01.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "Serializer.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Transform.h"
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
	Serializer::GetInstance()->SaveJson("json/temp/temp.json");


	//temp = new GameObject("temp", MODEL_TYPE::TRIANGLE);
	//Transform* trs=static_cast<Transform*>(temp->AddComponent_and_Get(Transform::TransformTypeName, new Transform(temp)));
	//Sprite* spr= static_cast<Sprite*>(temp->AddComponent_and_Get(Sprite::SpriteTypeName,new Sprite(temp)));
	//trs->SetPosition({ -20.f,0.f,0.f });
	//trs->SetScale({ 100.f,100.f,0.f });
}

void Stage01::Update()
{	
    auto in = InputManager::GetInstance();
}

void Stage01::Exit()
{	
	GameObjectManager::GetInstance()->DeleteAllObject();
}
