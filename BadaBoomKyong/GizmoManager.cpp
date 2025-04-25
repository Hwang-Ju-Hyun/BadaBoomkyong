#include "GizmoManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include <cassert>
#include <iostream>

GizmoManager::GizmoManager(){}

GizmoManager::~GizmoManager(){}  

void GizmoManager::Init(){}

void GizmoManager::Update()
{
	UpdateSelectedObject();
	MoveObject();
}

void GizmoManager::Exit(){}



void GizmoManager::CreateAxis(GameObject* _obj)
{
	if (_obj != nullptr)
	{						
		m_pAxis_X = new GameObject(Axis_X_Name, MODEL_TYPE::RECTANGLE);
		m_pAxis_Y = new GameObject(Axis_Y_Name, MODEL_TYPE::RECTANGLE);

		Transform* trs_x = dynamic_cast<Transform*>(m_pAxis_X->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_X)));				
		Sprite* spr_x=dynamic_cast<Sprite*>(m_pAxis_X->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_X)));		

		Transform* trs_y=dynamic_cast<Transform*>(m_pAxis_Y->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_Y)));		
		trs_y->SetAngle(90*(3.141592/180));
		Sprite* spr_y=dynamic_cast<Sprite*>(m_pAxis_Y->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_Y)));
		spr_y->SetColor({ 0.f,1.f,1.f,1.f });


		Transform* trs_TargetObj = dynamic_cast<Transform*>(_obj->FindComponent(Transform::TransformTypeName));
		
		assert(trs_x && trs_y && spr_x && spr_y&&trs_TargetObj);		
				
		trs_x->SetPosition({ trs_TargetObj->GetPosition().x + 50.f,trs_TargetObj->GetPosition().y,trs_TargetObj->GetPosition().z });
		trs_y->SetPosition({ trs_TargetObj->GetPosition().x,trs_TargetObj->GetPosition().y + 50.f,trs_TargetObj->GetPosition().z });
		
		trs_x->SetScale(m_vAxisScale);
		trs_y->SetScale(m_vAxisScale);
		m_bIsAxis_Selected = true;
	}
}

void GizmoManager::MoveObject()
{
	auto input = InputManager::GetInstance();
	//m_pPrevSelectedObject = m_pCurSelectedObject;
	if (m_pCurSelectedObject != nullptr)
	{
		Transform* selected_trs = dynamic_cast<Transform*>(m_pCurSelectedObject->FindComponent(Transform::TransformTypeName));
		if (selected_trs != nullptr)
		{
			//처음 오브젝트를 선택하였을때
			//축 생성
			if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
			{
				if (!m_bAxis_Actice_X&&!m_bAxis_Actice_Y)
				{
					if(!m_bIsAxis_Selected)
						CreateAxis(m_pCurSelectedObject);
				}
			}
			//축을 선택 후
			else if (m_bIsAxis_Selected &&input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT)
			{
				if (input->IsMouseInsideObject(m_pAxis_X))
				{
					m_bAxis_Actice_X = true;
					m_bAxis_Actice_Y = false;
				}
				else if (input->IsMouseInsideObject(m_pAxis_Y))
				{
					m_bAxis_Actice_Y = true;
					m_bAxis_Actice_X = false;
				}
				//X축 선택
				glm::vec2 cursor_pos = input->GetCursorPostion();		
				glm::vec3 obj_pos=selected_trs->GetPosition();
				if (m_bAxis_Actice_X&&!m_bAxis_Actice_Y)
				{					
					float offset_X = cursor_pos.x - obj_pos.x;
					Transform* trs_x = static_cast<Transform*>(m_pAxis_X->FindComponent(Transform::TransformTypeName));
					Transform* trs_y = static_cast<Transform*>(m_pAxis_Y->FindComponent(Transform::TransformTypeName));
					trs_x->AddPositionX(offset_X);
					trs_y->AddPositionX(offset_X);
					selected_trs->AddPositionX(offset_X);
				}
				else if (!m_bAxis_Actice_X && m_bAxis_Actice_Y)
				{
					/*float offset_Y = cursor_pos.y - obj_pos.y;
					Transform* trs_x = static_cast<Transform*>(m_pAxis_X->FindComponent(Transform::TransformTypeName));
					Transform* trs_y = static_cast<Transform*>(m_pAxis_Y->FindComponent(Transform::TransformTypeName));
					trs_x->AddPositionY(offset_Y);
					trs_y->AddPositionY(offset_Y);
					selected_trs->AddPositionY(offset_Y);*/
				}
			}
		}
	}
	else if (m_pCurSelectedObject == nullptr && m_pPrevSelectedObject != nullptr)
	{
		if (m_bIsAxis_Selected && input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT)
		{
			Transform* selected_trs = dynamic_cast<Transform*>(m_pPrevSelectedObject->FindComponent(Transform::TransformTypeName));
			if (input->IsMouseInsideObject(m_pAxis_X))
			{
				m_bAxis_Actice_X = true;
				m_bAxis_Actice_Y = false;
			}
			else if (input->IsMouseInsideObject(m_pAxis_Y))
			{
				m_bAxis_Actice_Y = true;
				m_bAxis_Actice_X = false;
			}
			//X축 선택
			glm::vec2 cursor_pos = input->GetCursorPostion();
			glm::vec3 obj_pos = selected_trs->GetPosition();
			if (m_bAxis_Actice_X && !m_bAxis_Actice_Y)
			{
				float offset_X = cursor_pos.x - obj_pos.x;
				Transform* trs_x = static_cast<Transform*>(m_pAxis_X->FindComponent(Transform::TransformTypeName));
				Transform* trs_y = static_cast<Transform*>(m_pAxis_Y->FindComponent(Transform::TransformTypeName));
				trs_x->AddPositionX(offset_X);
				trs_y->AddPositionX(offset_X);
				selected_trs->AddPositionX(offset_X);
			}
		}
	}
	else
	{
		Delete_Axis_And_Reset();
	}	
}

void GizmoManager::UpdateSelectedObject()
{		
	auto all_objs = GameObjectManager::GetInstance()->GetAllObjects();
	auto input = InputManager::GetInstance();		
	for (auto obj : all_objs)
	{				
		if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{				
			m_pCurSelectedObject = input->IsMouseInsideObject(obj);
			if (obj->GetName() == Axis_X_Name || obj->GetName() == Axis_Y_Name)
			{			
				return;
			}							
			else if (m_pCurSelectedObject != nullptr)
			{
				std::cout << m_pCurSelectedObject->GetName() << std::endl;
				m_pPrevSelectedObject = m_pCurSelectedObject;
				break;
			}
			else
			{
				 m_pPrevSelectedObject= m_pCurSelectedObject;
			}
		}		
	}			
}

void GizmoManager::Delete_Axis_And_Reset()
{
	if (m_pAxis_X != nullptr && m_pAxis_Y != nullptr)
	{
		GameObjectManager::GetInstance()->DeleteObject("Axis_X");
		GameObjectManager::GetInstance()->DeleteObject("Axis_Y");
	}
	m_bAxis_Actice_X = false;
	m_bAxis_Actice_Y = false;
	m_bIsAxis_Selected = false;
	//todo
	//m_pCurSelectedObject = nullptr;
}