#include "Stage03.h"
#include "ModelManager.h"
#include "Serializer.h"
#include "FactoryManager.h"
#include "ComponentManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "MainEditor.h"
#include "GameObjectManager.h"
#include "ObjectPoolManager.h"
#include "ResourceManager.h"

Stage03::Stage03(STAGE_TYPE _stageType,const std::string& _name)
	:BaseLevel(_stageType,_name)
{
}

Stage03::~Stage03()
{
}

void Stage03::Init()
{
	//ModelManager::GetInstance()->Init();

	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage03/Stage03_3D.json");
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
//	//FactoryManager    
//	FactoryManager::GetInstance()->Init();
//	//ComponentInit
//	ComponentManager::GetInstance()->Init();
//
//
//	//InputManager
//	InputManager::GetInstance()->Init();
//
//	//RenderInit            
//	RenderManager::GetInstance()->Init();
//	RenderManager::GetInstance()->InitDebugLineShader();
//#ifdef _DEBUG
//	MainEditor::GetInstance()->Init();
//#endif
}

void Stage03::Update()
{
}

void Stage03::Exit()
{
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage03/Stage03_3D.json", true);
	Serializer::GetInstance()->SaveJson_Object("json/Level/Stage03/Stage03_2D.json", false);
	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	GameObjectManager::GetInstance()->Exit();
	ResourceManager::GetInstance()->RemoveAllRes();
	ModelManager::GetInstance()->Exit();

	RenderManager::GetInstance()->Exit();
	EventManager::GetInstance()->Exit();

#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG
}
