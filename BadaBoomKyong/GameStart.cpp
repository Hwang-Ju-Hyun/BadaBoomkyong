#include "GameStart.h"
#include <glm.hpp>
#include "UICanvas.h"
#include "UIWidget.h"
#include "UIPanel.h"
#include "UIButton.h"
#include "TextureResource.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"
#include "UIText.h"
#include "BaseLevel.h";


GameStart::GameStart(STAGE_TYPE _stageType, const std::string& _name)
	:BaseLevel(_stageType,_name)
{
}

GameStart::~GameStart()
{
}
#include <iostream>
void GameStart::Init()
{		
	m_pUICanvas = new UICanvas(UIRenderSpace::SCREEN_SPACE);

	m_pUIBackCanvas = new UICanvas(UIRenderSpace::SCREEN_SPACE);


	UIWidget* btn_Widget = new UIWidget(m_pUICanvas);

	m_pUIStartBtn = new UIButton(btn_Widget->GetOwner(), 800.f, 400.f, 0.f, 355.f, 100.f);
	//TextureResource* hp_border_tex = m_pUIStartBtn->LoadTexture("HP_Bar", "../Extern/Assets/Texture/UI/Health_Bars/Borders/Border_Style_4.png");
	m_pUIStartBtn->SetPivot({ 0.f,0.f });
	m_pUIStartBtn->SetColor({ 1.0f,0.f,0.f,1.f });

	m_pUIEndBtn = new UIButton(btn_Widget->GetOwner(), 800.f, 800.f, 0.f, 355.f, 100.f);
	m_pUIEndBtn->SetPivot({ 0.0f, 0.0f });
	m_pUIEndBtn->SetColor({ 1.0f,1.f,0.f,1.f });
	//TextureResource* hp_bar_tex = m_pUIEndBtn->LoadTexture("HP_Bar", "../Extern/Assets/Texture/UI/Health_Bars/Style_1.png");

	m_pStartText = new UIText(btn_Widget->GetOwner(), "START", 80.f, 215.f, 1.f, glm::vec3{ 1.0f,0.5f,1.f, });
	m_pExitText =  new UIText(btn_Widget->GetOwner(), "EXIT", 110.f,-585.f, 1.f, glm::vec3{ 1.0f,0.5f,1.f, });


	UIWidget* back_ground_widget= new UIWidget(m_pUIBackCanvas);
	m_pUIBackground = new UIPanel(back_ground_widget->GetOwner(), 0.f, 980.f, 0.f, 1980.f, 980.f);
	m_pUIBackground->SetPivot({ 0.f,0.f });
	TextureResource* bar_tex = m_pUIBackground->LoadTexture("_Bar", "../Extern/Assets/Texture/background/background.png");



	m_pUICanvas->Init();
	m_pUIBackCanvas->Init();
	m_pUIBackCanvas->AddChild(back_ground_widget);
	back_ground_widget->AddChild(m_pUIBackground);

	m_pUICanvas->AddChild(btn_Widget);	
	btn_Widget->AddChild(m_pUIStartBtn);
	btn_Widget->AddChild(m_pUIEndBtn);
	m_pUIStartBtn->AddChild(m_pStartText);
	m_pUIEndBtn->AddChild(m_pExitText);

	m_pUIStartBtn->m_fpMouseOn = []() {GameObjectManager::GetInstance()->GameRestart();};

	BaseLevel* lvl_01 = GameStateManager::GetInstance()->FindLevel(STAGE_TYPE::STAGE_01);	

	m_pUIStartBtn->m_fpMouseClick = [lvl_01]() {GameStateManager::GetInstance()->ChangeLevel(lvl_01);};
	UIManager::GetInstance()->AddCanvas(m_pUIBackCanvas);
	UIManager::GetInstance()->AddCanvas(m_pUICanvas);
}

void GameStart::Update()
{

}

void GameStart::Exit()
{
}
