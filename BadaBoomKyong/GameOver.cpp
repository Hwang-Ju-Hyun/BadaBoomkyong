#include "GameOver.h"
#include "UICanvas.h"
#include "UIWidget.h"
#include "UIPanel.h"
#include "UIText.h"
#include "ComponentManager.h"
#include "MainEditor.h"
#include "Window.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"

GameOver::GameOver(STAGE_TYPE _stageType, const std::string& _name)
	:BaseLevel(_stageType, _name)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	m_pUIBackCanvas = new UICanvas(UIRenderSpace::SCREEN_SPACE);
	UIWidget* back_ground_widget = new UIWidget(m_pUIBackCanvas);
	m_pUIBackground = new UIPanel(back_ground_widget->GetOwner(), 0.f, 980.f, 0.f, 1980.f, 980.f);
	m_pUIBackground->SetPivot({ 0.f,0.f });
	TextureResource* bar_tex = m_pUIBackground->LoadTexture("GameOverBack", "../Extern/Assets/Texture/background/GameOverBack.png");

	back_ground_widget->AddChild(m_pReStartText);
	back_ground_widget->AddChild(m_pExitText);

	m_pReStartText = new UIText(back_ground_widget->GetOwner(), "RESTART", 80.f, 215.f, 1.f, glm::vec3{ 1.0f,0.5f,1.f, });
	m_pExitText = new UIText(back_ground_widget->GetOwner(), "EXIT", 110.f, -585.f, 1.f, glm::vec3{ 1.0f,0.5f,1.f, });

	UIManager::GetInstance()->AddCanvas(m_pUIBackCanvas);
}

void GameOver::Update()
{
}

void GameOver::Exit()
{
	UIManager::GetInstance()->Exit();
#ifdef _DEBUG
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG			
	ComponentManager::GetInstance()->Exit();
	GameObjectManager::GetInstance()->Exit();
	
}
