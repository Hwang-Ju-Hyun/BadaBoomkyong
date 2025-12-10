#include "Congratulation.h"
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
#include "RenderManager.h"
#include "InputManager.h"
#include "EventManager.h"

Congratulation::Congratulation(STAGE_TYPE _stageType, const std::string& _name)
	:BaseLevel(_stageType, _name)
{
}

Congratulation::~Congratulation()
{
}

void Congratulation::Init()
{
#ifdef _DEBUG	
	MainEditor::GetInstance()->Init();
#endif
	RenderManager::GetInstance()->Init();
	UIManager::GetInstance()->Init();

	m_pUIBackCanvas = new UICanvas(UIRenderSpace::SCREEN_SPACE);
	m_pUIBackCanvas->Init();

	UIWidget* back_ground_widget = new UIWidget(m_pUIBackCanvas);
	m_pUIBackCanvas->AddChild(back_ground_widget);

	//m_pUIBackground = new UIText(back_ground_widget->GetOwner(), "GAME OVER", 80.f, 15.f, 2.f, glm::vec3{ 1.0f,0.5f,1.f, });
	//m_pUIBackground->SetPivot({ 0.f,0.f });
	//TextureResource* bar_tex = m_pUIBackground->LoadTexture("GameOverBack", "../Extern/Assets/Texture/background/GameOverBack.png");
	m_pConText = new UIText(back_ground_widget->GetOwner(), "CONGRATULATION", 550.f, 600.f, 1.5f, glm::vec3{ 1.0f,1.0f,1.f, });	
	m_pExitText = new UIText(back_ground_widget->GetOwner(), "EXIT - E", 700.f, 215, 1.f, glm::vec3{ 1.0f,0.5f,1.f, });

	back_ground_widget->AddChild(m_pConText);	
	back_ground_widget->AddChild(m_pExitText);

	UIManager::GetInstance()->AddCanvas(m_pUIBackCanvas);
}

void Congratulation::Update()
{
	if (InputManager::GetInstance()->GetKetCode(GLFW_KEY_E) == GLFW_PRESS)
	{
		EventManager::GetInstance()->LevelChange(nullptr);
	}
}

void Congratulation::Exit()
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
