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
#include "GeometryUtill.h"
#include "FrameBuffer.h"

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

	const auto width = Window::GetInstance()->GetWindowWidth();
	const auto height = Window::GetInstance()->GetWindowHeight();

}

void MainEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();	
	
	//UpdateSelectedObjectByLevel();
	/*if (m_pTransform_SelectedObj_Level != nullptr)
	{
		glm::mat4 model = m_pTransform_SelectedObj_Level->GetModelToWorld_Matrix();
		DrawGizmo(model, m_pCam->GetViewMatrix(), m_pCam->GetProjMatrix());
		std::cout << m_pTransform_SelectedObj_Level->GetOwner()->GetName() << std::endl;
	}*/

	ObjectPannelDraw();	
	TopMenuBarDraw();
	
}

void MainEditor::Exit()
{

}

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
	const char* CreateObject_PopUp_Title = "CreateObject";
	static size_t Selected_ModelType=-1;
	static char objectNameBuffer[128] = "NewObject";
	static bool ShowCreateObjectWindow = false;
	static bool Is3D = false;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::Button("Create Object"))
		{
			ImGui::OpenPopup(CreateObject_PopUp_Title);
		}

		if (ImGui::BeginPopup(CreateObject_PopUp_Title))
		{
			std::vector<Model*> models = ModelManager::GetInstance()->GetAllModels();
			for (auto m : models)
			{
				if (ImGui::MenuItem(m->GetName().c_str()))
				{					
					Selected_ModelType = static_cast<size_t>(m->GetModelType());
					ShowCreateObjectWindow = true;
					Selected_ModelType >= 4 ? Is3D = true : Is3D = false;
					ImGui::CloseCurrentPopup();
					break;
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

	if (ShowCreateObjectWindow)
	{		
		ImGui::OpenPopup("Enter Object Name");
		if (ImGui::BeginPopupModal("Enter Object Name", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("Enter a name for the new object:");
			ImGui::InputText("Name", objectNameBuffer, IM_ARRAYSIZE(objectNameBuffer));

			if()


			if (ImGui::Button("Create"))
			{
				// TODO: 오브젝트 생성 로직 구현
				// 예: ObjectManager::GetInstance()->CreateObject(selectedModelName, objectNameBuffer);

				GameObjectManager::GetInstance()->AddObject(new GameObject(objectNameBuffer,Selected_ModelType,)

				ShowCreateObjectWindow = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				ShowCreateObjectWindow = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
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

//Chat GPT 쓴 함수
void MainEditor::DrawGizmo(glm::mat4& _modelMatrix, const glm::mat4& _viewMatrix, const glm::mat4& _projectionMatrix)
{
	ImGuizmo::BeginFrame(); // 필수: 내부 상태 초기화
	// 1. ImGuizmo 설정
	ImGuizmo::SetOrthographic(false); // Perspective 모드 사용
	ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

	// 화면 전체 기준으로 좌표 잡기
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
	float width = Window::GetInstance()->GetWindowWidth();
	float height = Window::GetInstance()->GetWindowHeight();
    ImGuizmo::SetRect(0, 0, width, height);
	
	// 3. 조작 모드 선택 (이동 / 회전 / 스케일)
	static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
	static ImGuizmo::MODE currentGizmoMode = ImGuizmo::LOCAL;
	
	// 키 입력으로 조작 모드 전환 (선택 사항)
	if (ImGui::IsKeyPressed(ImGuiKey_T))
		currentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(ImGuiKey_R))
		currentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(ImGuiKey_Y))
		currentGizmoOperation = ImGuizmo::SCALE;	
	
	// 4. 오브젝트의 월드 좌표를 사용해 Gizmo를 그린다.	
	bool changed =ImGuizmo::Manipulate(
		glm::value_ptr(_viewMatrix),
		glm::value_ptr(_projectionMatrix),
		currentGizmoOperation,
		currentGizmoMode,
		glm::value_ptr(_modelMatrix)
	);
	if (changed)
	{
		glm::vec3 translation, rotation, scale;
		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(_modelMatrix), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));

		// 회전은 degree 단위임
		if (m_pTransform_SelectedObj_Level)
		{
			m_pTransform_SelectedObj_Level->SetPosition(translation);
			m_pTransform_SelectedObj_Level->SetRotation(rotation); // 회전 저장 방식에 맞게 처리 필요 (Euler/Quaternion)
			m_pTransform_SelectedObj_Level->SetScale(scale);
		}
	}
}
#endif // DEBUG