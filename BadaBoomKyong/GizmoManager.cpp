#include "GizmoManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include "Sprite.h"
#include <cassert>
#include <iostream>

#ifdef _GIZMO
GizmoManager::GizmoManager(){}

GizmoManager::~GizmoManager(){}  

void GizmoManager::Init(){}

void GizmoManager::Update()
{
//	UpdateSelectedObject();
//	MoveObject();
}

void GizmoManager::Exit(){}

void GizmoManager::Delete_Axis_And_Reset()
{
	if (m_pAxis_X != nullptr && m_pAxis_Y != nullptr)
	{
		GameObjectManager::GetInstance()->DeleteObject("Axis_X");
		GameObjectManager::GetInstance()->DeleteObject("Axis_Y");
	}
	
}

void GizmoManager::CreateAxis(GameObject* _obj)
{
	if (_obj != nullptr)
	{
		m_pAxis_X = new GameObject(Axis_X_Name, MODEL_TYPE::RECTANGLE);
		m_pAxis_Y = new GameObject(Axis_Y_Name, MODEL_TYPE::RECTANGLE);

		Transform* trs_x = dynamic_cast<Transform*>(m_pAxis_X->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_X)));
		Sprite* spr_x = dynamic_cast<Sprite*>(m_pAxis_X->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_X)));

		Transform* trs_y = dynamic_cast<Transform*>(m_pAxis_Y->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_Y)));
		trs_y->SetAngle(90 * (3.141592 / 180));
		Sprite* spr_y = dynamic_cast<Sprite*>(m_pAxis_Y->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_Y)));
		spr_y->SetColor({ 0.f,1.f,1.f,1.f });


		Transform* trs_TargetObj = dynamic_cast<Transform*>(_obj->FindComponent(Transform::TransformTypeName));

		assert(trs_x && trs_y && spr_x && spr_y && trs_TargetObj);

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
	if (m_pCurSelectedObject)
	{
		Transform* selected_trs = dynamic_cast<Transform*>(m_pCurSelectedObject->FindComponent(Transform::TransformTypeName));
		if (!m_bIsAxis_Selected && input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			Delete_Axis_And_Reset();
			CreateAxis(m_pCurSelectedObject);
			m_bIsAxis_Selected = true;
		}
		else if (m_bIsAxis_Selected && input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT)
		{
			glm::vec2 cursor_pos = input->GetCursorPostion();
			glm::vec3 obj_pos = selected_trs->GetPosition();

			float offset_X = cursor_pos.x - obj_pos.x;
			Transform* trs_x = static_cast<Transform*>(m_pAxis_X->FindComponent(Transform::TransformTypeName));
			Transform* trs_y = static_cast<Transform*>(m_pAxis_Y->FindComponent(Transform::TransformTypeName));
			trs_x->AddPositionX(offset_X);
			trs_y->AddPositionX(offset_X);
			selected_trs->AddPositionX(offset_X);
		}	
	}
	else
	{
		Delete_Axis_And_Reset();
		m_bIsAxis_Selected = false;
	}
}

void GizmoManager::UpdateSelectedObject()
{
	auto input = InputManager::GetInstance();
	auto objs = GameObjectManager::GetInstance()->GetAllObjects();
	if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		for (auto obj : objs)
		{			
			if (obj->GetName() == Axis_X_Name || obj->GetName() == Axis_Y_Name)
			{
				//해당 조건문에 들어갔다는 것은 SelectedObject가 있다는 소리자나
				m_pCurSelectedObject = nullptr;
				break;
			}
			else if (input->IsMouseInsideObject(obj))
			{
				m_pCurSelectedObject = obj;
				return;
			}
		}
		if(!m_bIsAxis_Selected)
			m_pCurSelectedObject = nullptr;
	}		
}
#endif