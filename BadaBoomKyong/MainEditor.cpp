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
#include "RenderManager.h"
#include "Camera.h"

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
	m_pCam=RenderManager::GetInstance()->GetCamera();
}

void MainEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	
	UpdateSelectedObjectByLevel();
	if (m_pTransform_SelectedObj_Level != nullptr)
	{
		glm::mat4 model = m_pTransform_SelectedObj_Level->GetModelToWorld_Matrix();
		DrawGizmo(model, m_pCam->GetViewMatrix(), m_pCam->GetProjMatrix());
		std::cout << m_pTransform_SelectedObj_Level->GetOwner()->GetName() << std::endl;
	}				
	//ObjectPannelDraw();
	////GizmoManager::GetInstance()->Update();

	////TopMenuBarDraw();
	////InputManager::GetInstance()->PrintCursorPosInConsole();	
	
	//ImGui::End();
}

#include "GeometryUtill.h"

void MainEditor::UpdateSelectedObjectByLevel()
{
	const auto input = InputManager::GetInstance();
	const auto all_obj=GameObjectManager::GetInstance()->GetAllObjects();
	const glm::vec2 cursor=input->GetCursorPostion();

	for (auto obj : all_obj)
	{
		Transform* obj_trs = dynamic_cast<Transform*>(obj->FindComponent(Transform::TransformTypeName));
		if (obj_trs == nullptr)
			continue;
		if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			bool IsInside = GeometryUtil::GetInstance()->IsPointInsideRectangle(cursor, obj_trs);
			m_pSelectedObjByLevel = obj;
			m_pTransform_SelectedObj_Level = obj_trs;
			return;
		}		
	}		
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

//Chat GPT 쓴 함수
void MainEditor::DrawGizmo(glm::mat4& _modelMatrix, const glm::mat4& _viewMatrix, const glm::mat4& _projectionMatrix)
{
	// 1. ImGuizmo 설정
	ImGuizmo::SetOrthographic(false); // Perspective 모드 사용
	ImGuizmo::SetDrawlist();

	// 현재 ImGui 창의 위치와 크기를 가져옴
	ImVec2 winPos = ImGui::GetWindowPos();
	ImVec2 winSize = ImGui::GetWindowSize();
		
	auto w = Window::GetInstance()->GetWindowWidth();
	auto h = Window::GetInstance()->GetWindowHeight();

	//// 2D 화면 좌표계를 ImGuizmo로 전달하기 위해 뷰포트를 설정
	ImGuizmo::SetRect(-w/2,-h/2,w, h);

	// 3. 조작 모드 선택 (이동 / 회전 / 스케일)
	static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
	static ImGuizmo::MODE currentGizmoMode = ImGuizmo::LOCAL;

	// 키 입력으로 조작 모드 전환 (선택 사항)
	if (ImGui::IsKeyPressed(ImGuiKey_T))
		currentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(ImGuiKey_R))
		currentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(ImGuiKey_S))
		currentGizmoOperation = ImGuizmo::SCALE;	

	// 4. 오브젝트의 월드 좌표를 사용해 Gizmo를 그린다.
	ImGuizmo::Manipulate(
		glm::value_ptr(_viewMatrix),
		glm::value_ptr(_projectionMatrix),
		currentGizmoOperation,
		currentGizmoMode,
		glm::value_ptr(_modelMatrix)
	);
}
#endif // DEBUG