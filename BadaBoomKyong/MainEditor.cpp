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
#include "GameStateManager.h"
#include "BaseLevel.h"

#ifdef _DEBUG
MainEditor::MainEditor(){}
MainEditor::~MainEditor(){}

bool MainEditor::init_edit = false;
void MainEditor::Init()
{
	//ImGui Init

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
	init_edit = true;

	m_pCam=RenderManager::GetInstance()->GetCamera();

	const auto width = Window::GetInstance()->GetWindowWidth();
	const auto height = Window::GetInstance()->GetWindowHeight();

}

void MainEditor::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();		

	ObjectPannelDraw();	
	TopMenuBarDraw();
	DeletObjectModal();
	
	UpdateEditorCameraControls();

	DrawGizmo();
}

static bool openDeletePopup = false;
static std::string deletePopupName = "";

void MainEditor::DeletObjectModal()
{
	if (ImGui::IsKeyPressed(ImGuiKey_Delete) && m_pSelectedObjByPannel)
	{
		deletePopupName = "Delete Object" + m_pSelectedObjByPannel->GetName() + std::to_string(m_pSelectedObjByPannel->GetID());
		openDeletePopup = true;
	}

	if (openDeletePopup)
	{
		ImGui::OpenPopup(deletePopupName.c_str());
		openDeletePopup = false;
	}

	if (ImGui::BeginPopupModal(deletePopupName.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Are you sure you want to delete '%s'?", (m_pSelectedObjByPannel->GetName()+ std::to_string(m_pSelectedObjByPannel->GetID())).c_str());
		if (ImGui::Button("YES"))
		{
			GameObjectManager::GetInstance()->DeleteObject(m_pSelectedObjByPannel->GetName(), m_pSelectedObjByPannel->GetID());
			m_pSelectedObjByPannel = nullptr;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("NO"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
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
					if (Selected_ModelType == MODEL_TYPE::CUSTOM_MODEL)
					{
						custom_model_path = m->GetPath();
					}
					else
					{
						custom_model_path= "Not CustomModel";
					}
					ImGui::CloseCurrentPopup();
					break;
				}
			}								
			ImGui::EndPopup();
		}
		if (ImGui::MenuItem("SAVE"))
		{
			BaseLevel* cur_level = GameStateManager::GetInstance()->GetCurrentLevel();
			if(cur_level->GetName()=="Stage01")
				Serializer::GetInstance()->SaveJson_Object("json/Level/Stage01/Stage01_3D.json",true);
			else if(cur_level->GetName()=="Stage02")
				Serializer::GetInstance()->SaveJson_Object("json/Level/Stage02/Stage02_3D.json", true);
			else if(cur_level->GetName()=="StageTest")
				Serializer::GetInstance()->SaveJson_Object("json/Level/StageTest/StageTest_3D.json", true);
			//Serializer::GetInstance()->SaveJson_Object("json/temp/temp.json",false);
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

			if (ImGui::Button("Create"))
			{			
				GameObject* obj=new GameObject(objectNameBuffer, MODEL_TYPE(Selected_ModelType));
				
				if (Selected_ModelType == MODEL_TYPE::CUSTOM_MODEL)
				{
					auto model_mgr = ModelManager::GetInstance();
					Model* custom_model = model_mgr->LoadModel(custom_model_path);
					obj->SetModel(custom_model);
				}
				else
				{
					Sprite* spr = static_cast<Sprite*>(obj->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(obj)));
				}
				Transform* trs= static_cast<Transform*>(obj->AddComponent_and_Get(Transform::TransformTypeName, new Transform(obj)));				

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
	auto obj_mgr = GameObjectManager::GetInstance();
	auto all_objs = obj_mgr->GetAllObjects();
	ImGui::Begin("Object List");

	for (int i = 0;i < all_objs.size();i++)
	{		
		if (ImGui::Button((all_objs[i]->GetName() + std::to_string(all_objs[i]->GetID())).c_str()))
		{
			m_pSelectedObjByPannel = all_objs[i];
			m_pTransform_SelectedObj = dynamic_cast<Transform*>(m_pSelectedObjByPannel->FindComponent(Transform::TransformTypeName));
		}
		if (m_pSelectedObjByPannel == all_objs[i])
		{
			std::unordered_map<std::string, BaseComponent*> comps = all_objs[i]->GetAllComponentsOfObj_Hash();
			for (auto iter = comps.begin(); iter != comps.end(); ++iter)
			{
				BaseComponent* comp = iter->second;
				if (comp!=nullptr&&ImGui::TreeNode(comp->GetName().c_str()))
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

//Chat GPT �� �Լ�
void MainEditor::DrawGizmo()
{
	if (m_pTransform_SelectedObj == nullptr)
		return;

	ImGuizmo::BeginFrame(); // �ʼ�: ���� ���� �ʱ�ȭ

	// 1. ImGuizmo ����
	ImGuizmo::SetOrthographic(false); // Perspective ��� ���
	ImGuizmo::SetDrawlist(ImGui::GetBackgroundDrawList());

	// ȭ�� ��ü �������� ��ǥ ���
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
	float width = static_cast<float>(Window::GetInstance()->GetWindowWidth());
	float height = static_cast<float>(Window::GetInstance()->GetWindowHeight());
    ImGuizmo::SetRect(0, 0, width, height);
	
	// 3. ���� ��� ���� (�̵� / ȸ�� / ������)
	static ImGuizmo::OPERATION currentGizmoOperation = ImGuizmo::TRANSLATE;
	static ImGuizmo::MODE currentGizmoMode = ImGuizmo::LOCAL;
	
	// Ű �Է����� ���� ��� ��ȯ (���� ����)
	if (ImGui::IsKeyPressed(ImGuiKey_T))
		currentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(ImGuiKey_R))
		currentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(ImGuiKey_Y))
		currentGizmoOperation = ImGuizmo::SCALE;	
		
	glm::mat4 ModelMatrix = m_pTransform_SelectedObj->GetModelToWorld_Matrix();
	glm::mat4 ViewMatrix = m_pCam->GetViewMatrix();
	glm::mat4 ProjMatrix = m_pCam->GetProjMatrix();
	
	// 4. ������Ʈ�� ���� ��ǥ�� ����� Gizmo�� �׸���.	
	bool changed =ImGuizmo::Manipulate(
		glm::value_ptr(ViewMatrix),
		glm::value_ptr(ProjMatrix),
		currentGizmoOperation,
		currentGizmoMode,
		glm::value_ptr(ModelMatrix)
	);

	if (changed)
	{		
		glm::vec3 translation, rotation, scale;
		ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(ModelMatrix), glm::value_ptr(translation), glm::value_ptr(rotation), glm::value_ptr(scale));

		// ȸ���� degree ������
		if (m_pTransform_SelectedObj)
		{
			m_pTransform_SelectedObj->SetPosition(translation);
			m_pTransform_SelectedObj->SetRotation(rotation); // ȸ�� ���� ��Ŀ� �°� ó�� �ʿ� (Euler/Quaternion)
			m_pTransform_SelectedObj->SetScale(scale);
		}
	}
}

void MainEditor::UpdateEditorCameraControls()
{
	auto input = InputManager::GetInstance();
	static glm::vec2 prevMousePos = { 0.f, 0.f };
	static bool isFirst = true;

	if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS ||
		input->GetMouseBtn(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_REPEAT)
	{
		glm::vec2 currMousePos = input->GetCursorPostion();
		if (isFirst)
		{
			prevMousePos = currMousePos;
			isFirst = false;
		}

		glm::vec2 delta = currMousePos - prevMousePos;
		prevMousePos = currMousePos;

		float sensitivity = 0.1f;
		m_pCam->yaw += delta.x * sensitivity;
		m_pCam->pitch += delta.y * sensitivity;

		// pitch ����
		//if (m_pCam->pitch > 89.0f) m_pCam->pitch = 89.0f;
		//if (m_pCam->pitch < -89.0f) m_pCam->pitch = -89.0f;


		// �̵� WASD (ī�޶� ���� �������� �̵�)
		glm::vec3 moveDir{ 0.0f };
		float speed = 25.f;
		if (input->GetKetCode(GLFW_KEY_W) == GLFW_REPEAT)
			moveDir += m_pCam->m_vCamFront;
		if (input->GetKetCode(GLFW_KEY_S) == GLFW_REPEAT)
			moveDir -= m_pCam->m_vCamFront;
		if (input->GetKetCode(GLFW_KEY_A) == GLFW_REPEAT)
			moveDir -= m_pCam->m_vCamRight;
		if (input->GetKetCode(GLFW_KEY_D) == GLFW_REPEAT)
			moveDir += m_pCam->m_vCamRight;
		if (input->GetKetCode(GLFW_KEY_E) == GLFW_REPEAT)
			moveDir += m_pCam->m_vCamUp;
		//todo : �ʿ�� �ּ�Ǫ��
		/*if (input->GetKetCode(GLFW_KEY_Q) == GLFW_REPEAT)
			moveDir -= m_pCam->m_vCamUp;*/

		if (glm::length(moveDir) > 0.0f)
		{
			moveDir = glm::normalize(moveDir);
			m_pCam->AddPosition(moveDir * speed);
		}
	}
	else
	{
		isFirst = true;
	}
}
#endif // DEBUG