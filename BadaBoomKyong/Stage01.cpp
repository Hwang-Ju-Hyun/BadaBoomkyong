#include "Stage01.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "Transform.h"
#include "Serializer.h"
#include "Sprite.h"
#include "InputManager.h"
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
}

void Stage01::Update()
{	
    auto in = InputManager::GetInstance();
}

void Stage01::Exit()
{	
	GameObjectManager::GetInstance()->DeleteAllObject();
}
