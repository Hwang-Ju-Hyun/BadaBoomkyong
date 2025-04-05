#include "Stage01.h"
#include "GameObject.h"
#include "GameObjectManager.h"

Stage01::Stage01(const std::string& _name)
	:BaseLevel(_name)
{
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{
	const std::string str = "rect";	
	temp = new GameObject(str, MODEL_TYPE::TRIANGLE);
}

void Stage01::Update()
{	
	
}

void Stage01::Exit()
{	
	GameObjectManager::GetInstance()->DeleteAllObject();
}
