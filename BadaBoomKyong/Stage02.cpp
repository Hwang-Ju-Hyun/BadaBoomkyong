#include "Stage02.h"
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
#include "ModelManager.h"
#include "FactoryManager.h"
#include "MainEditor.h"
#include "RenderManager.h"
Stage02::Stage02(const std::string& _name)
	:BaseLevel(_name)
{
}

Stage02::~Stage02()
{
}

void Stage02::Init()
{	
	ModelManager::GetInstance()->Init();
	
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage02/Stage02_3D.json");

	//FactoryManager    
	FactoryManager::GetInstance()->Init();
	//ComponentInit
	ComponentManager::GetInstance()->Init();
	

	 //InputManager
	InputManager::GetInstance()->Init();

	//RenderInit            
	RenderManager::GetInstance()->Init();
	RenderManager::GetInstance()->InitDebugLineShader();	
#ifdef _DEBUG
	MainEditor::GetInstance()->Init();
#endif
}

void Stage02::Update()
{
}

void Stage02::Exit()
{
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_3D.json", true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_2D.json", false);
	ComponentManager::GetInstance()->Exit();
	GameObjectManager::GetInstance()->DeleteAllObject();
}