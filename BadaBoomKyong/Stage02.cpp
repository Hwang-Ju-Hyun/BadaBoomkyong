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
#include "ObjectPoolManager.h"
#include "ResourceManager.h"
#include "Stage03.h"
#include "GameStateManager.h"


#include "UICanvas.h"
#include "UIWidget.h"
#include "UIButton.h"
#include "UIManager.h"
#include "UIPanel.h"

Stage02::Stage02(STAGE_TYPE _stageType,const std::string& _name)
	:BaseLevel(_stageType,_name)
{
	//lvl_3 = new Stage03(STAGE_TYPE::STAGE_03,"Stage03");
}

Stage02::~Stage02()
{
}

void Stage02::Init()
{	
	Serializer::GetInstance()->LoadJson_Object("json/Level/Stage02/Stage02_3D.json");		
	
	//FactoryManager::GetInstance()->Init();

	//ComponentInit
	//ComponentManager::GetInstance()->Init();

	//InputManager
	//InputManager::GetInstance()->Init();

	//RenderInit            
	//RenderManager::GetInstance()->Init();
	//RenderManager::GetInstance()->InitDebugLineShader();


	FactoryManager::GetInstance()->Init();

	ComponentManager::GetInstance()->Init();

	RenderManager::GetInstance()->Init();
	RenderManager::GetInstance()->InitDebugLineShader();
	//RenderManager::GetInstance()->Init();
	//RenderManager::GetInstance()->InitDebugLineShader();


#ifdef _DEBUG	
	MainEditor::GetInstance()->Init();
#endif
	UIManager::GetInstance()->Init();

#ifdef _DEBUG	
	//MainEditor::GetInstance()->Init();
#endif

	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::MONSTER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::MONSTER);
	//CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PORTAL);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MELEE, GROUP_TYPE::PLAYER);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::PLAYER, GROUP_TYPE::DEATH_ZONE);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::MONSTER, GROUP_TYPE::PLATFORM);
	CollisionManager::GetInstance()->CheckCollision(GROUP_TYPE::BULLET, GROUP_TYPE::PLATFORM);


	/*UICanvas* canvas = new UICanvas(UIRenderSpace::WORLD_SPACE);
	UIWidget* widget = new UIWidget(canvas);
	UIButton* btn = new UIButton(widget->GetOwner(), 228.353f, 641.322f, 597.875f, 1000.f, 10000.f);
	canvas->Init();
	widget->AddChild(btn);
	canvas->AddChild(widget);


	UICanvas* canvas_s = new UICanvas(UIRenderSpace::SCREEN_SPACE);
	UIWidget* widget_s = new UIWidget(canvas_s);
	UIPanel* panel_s = new UIPanel(widget_s->GetOwner(), 1080.f, 800.f,0.f, 50.f, 50.f);

	canvas_s->Init();
	widget_s->AddChild(panel_s);
	canvas_s->AddChild(widget_s);

	panel_s->m_fpMouseOn = []() {GameObjectManager::GetInstance()->GameRestart();};

	UIManager::GetInstance()->AddCanvas(canvas);
	UIManager::GetInstance()->AddCanvas(canvas_s);*/
}

void Stage02::Update()
{
	
}

void Stage02::Exit()
{
	//Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_3D.json", true);
	//Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_2D.json", false);
	
	FactoryManager::GetInstance()->Exit();
	ObjectPoolManager::GetInstance()->Exit();

	EventManager::GetInstance()->Exit();
	UIManager::GetInstance()->Exit();
	GameObjectManager::GetInstance()->Exit();
	//ResourceManager::GetInstance()->RemoveAllRes();
	//ModelManager::GetInstance()->Exit();

	RenderManager::GetInstance()->Exit();

#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG	
}