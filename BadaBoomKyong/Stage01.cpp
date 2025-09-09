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
#include "RenderManager.h"
#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "ModelManager.h"
#include "FactoryManager.h"
#include "RenderManager.h"
#include "MainEditor.h"


Stage01::Stage01(STAGE_TYPE _stageType, const std::string& _name)
	:BaseLevel(_stageType,_name)
{
	//lvl_2 = new Stage02(STAGE_TYPE::STAGE_02,"Stage02");
}

Stage01::~Stage01()
{
}

void Stage01::Init()
{			
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage01/Stage01_3D.json");
	//Serializer::GetInstance()->LoadJson_Object("json/temp/temp.json");		
	
	
	FactoryManager::GetInstance()->Init();

	//ComponentInit
	ComponentManager::GetInstance()->Init();	

	//RenderInit            
	RenderManager::GetInstance()->Init();
	RenderManager::GetInstance()->InitDebugLineShader();


#ifdef _DEBUG
	//MainEditor
	MainEditor::GetInstance()->Init();
#endif   
}

void Stage01::Update()
{				
	
}


void Stage01::Exit()
{	
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_3D.json",true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_2D.json", false);
	ComponentManager::GetInstance()->Exit();
	
	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	GameObjectManager::GetInstance()->Exit();
	ResourceManager::GetInstance()->RemoveAllRes();
	//ModelManager::GetInstance()->Exit();
	
	RenderManager::GetInstance()->Exit();
	EventManager::GetInstance()->Exit();


}