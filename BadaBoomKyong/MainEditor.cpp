#include "MainEditor.h"
#include "Window.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GizmoManager.h"
#include "Serializer.h"
#include "ModelManager.h"
#include <iostream>

#ifdef _DEBUG
MainEditor::MainEditor(){}
MainEditor::~MainEditor(){}

void MainEditor::Init()
{
	//ImGui Init
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls	
		ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		auto window_handle = Window::GetInstance()->GetWindowHandle();
		ImGui_ImplGlfw_InitForOpenGL(window_handle, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
	}	
}

void MainEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ObjectPannelDraw();
	//GizmoManager::GetInstance()->Update();
	TopMenuBarDraw();
	//InputManager::GetInstance()->PrintCursorPosInConsole();
}

void MainEditor::TopMenuBarDraw()
{	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::Button("Create Object"))
		{
			ImGui::OpenPopup(m_sCreateObject_PopUp_Title);
		}

		if (ImGui::BeginPopup(m_sCreateObject_PopUp_Title))
		{
			std::vector<Model*> models = ModelManager::GetInstance()->GetAllModels();
			for (auto m : models)
			{
				if (ImGui::MenuItem(m->GetName().c_str()))
				{
					
				}
			}								
			ImGui::EndPopup();
		}
		if (ImGui::MenuItem("SAVE"))
		{
			/*Serializer::GetInstance()->SaveJson_Object("json/temp/temp_3D.json");
			Serializer::GetInstance()->SaveJson_Object("json/temp/temp.json");*/
		}				
		ImGui::EndMainMenuBar();
	}
}

void MainEditor::ObjectPannelDraw()
{
	auto ObjMgr = GameObjectManager::GetInstance();

	ImGui::Begin("Object List");

	for (auto obj : ObjMgr->GetAllObjects())
	{		
		if (ImGui::Button(obj->GetName().c_str()))
		{
			m_pSelectedObjByButton = obj;		
		}
		if (m_pSelectedObjByButton == obj)
		{			
			std::unordered_map<std::string, BaseComponent*> comps = obj->GetAllComponentsOfObj_Hash();
			for (auto iter = comps.begin(); iter != comps.end(); ++iter)
			{
				BaseComponent* comp = iter->second;
				if (ImGui::TreeNode(comp->GetName().c_str()))
				{
					comp->EditInfoFromButton();
					ImGui::TreePop();
				}
			}
			ImGui::Separator();
		}
	}
	ImGui::End();	
}


void MainEditor::Draw_ObjectInfoPannel()
{

}
#endif // DEBUG