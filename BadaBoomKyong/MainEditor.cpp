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
	GameObject* g = GameObjectManager::GetInstance()->FindObject("WALL_BACK");	
	m_pTransform_SelectedObj_Level = static_cast<Transform*>(g->FindComponent(Transform::TransformTypeName));

	m_pCam=RenderManager::GetInstance()->GetCamera();
}

void MainEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	
	//UpdateSelectedObjectByLevel();
	if (m_pTransform_SelectedObj_Level != nullptr)
	{
		auto g=GameObjectManager::GetInstance()->FindObject("WALL_BACK");		
		glm::mat4 model = m_pTransform_SelectedObj_Level->GetModelToWorld_Matrix();
		DrawGizmo(model, m_pCam->GetViewMatrix(), m_pCam->GetProjMatrix());
		std::cout << m_pTransform_SelectedObj_Level->GetOwner()->GetName() << std::endl;
	}				
	//ObjectPannelDraw();
	//GizmoManager::GetInstance()->Update();

	//TopMenuBarDraw();
	//InputManager::GetInstance()->PrintCursorPosInConsole();	
	
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
}


void MainEditor::Draw_ObjectInfoPannel()
{

}

//Chat GPT 쓴 함수
void MainEditor::DrawGizmo(glm::mat4& _modelMatrix, const glm::mat4& _viewMatrix, const glm::mat4& _projectionMatrix)
{
	ImGuizmo::BeginFrame(); // 필수: 내부 상태 초기화
	// 1. ImGuizmo 설정
	ImGuizmo::SetOrthographic(false); // Perspective 모드 사용
	ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

// 화면 전체 기준으로 좌표 잡기
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImGuizmo::SetRect(0, 0, displaySize.x, displaySize.y);
	
	// 3. 조작 모드 선택 (이동 / 회전 / 스케일)
	static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
	static ImGuizmo::MODE currentGizmoMode = ImGuizmo::WORLD;
	
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