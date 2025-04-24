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
		m_pAxis_X = new GameObject("Axis_X", MODEL_TYPE::LINE);
		m_pAxis_Y = new GameObject("Axis_Y", MODEL_TYPE::LINE);

		Transform* trs_x = dynamic_cast<Transform*>(m_pAxis_X->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_X)));				
		Sprite* spr_x=dynamic_cast<Sprite*>(m_pAxis_X->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_X)));		

		Transform* trs_y=dynamic_cast<Transform*>(m_pAxis_Y->AddComponent_and_Get(Transform::TransformTypeName, new Transform(m_pAxis_Y)));		
		trs_y->SetAngle(90*(3.141592/180));
		Sprite* spr_y=dynamic_cast<Sprite*>(m_pAxis_Y->AddComponent_and_Get(Sprite::SpriteTypeName, new Sprite(m_pAxis_Y)));
		spr_y->SetColor({ 0.f,1.f,1.f,1.f });


		Transform* trs_TargetObj = dynamic_cast<Transform*>(_obj->FindComponent(Transform::TransformTypeName));
		
		assert(trs_x && trs_y && spr_x && spr_y&&trs_TargetObj);

		glm::vec3 axis_scale = {100.f,100.f,100.f };
				
		trs_x->SetPosition({ trs_TargetObj->GetPosition().x + 50.f,trs_TargetObj->GetPosition().y,trs_TargetObj->GetPosition().z });
		trs_y->SetPosition({ trs_TargetObj->GetPosition().x,trs_TargetObj->GetPosition().y + 50.f,trs_TargetObj->GetPosition().z });
		
		trs_x->SetScale(axis_scale);
		trs_y->SetScale(axis_scale);
	}
}

void GizmoManager::MoveObject()
{
	auto input = InputManager::GetInstance();
	if (m_pSelectedObject != nullptr)
	{
		Transform* selected_trs = dynamic_cast<Transform*>(m_pSelectedObject->FindComponent(Transform::TransformTypeName));
		if (selected_trs != nullptr)
		{
			//처음 오브젝트를 선택하였을때
			//축 생성
			if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				if (!m_bAxis_Actice)
				{
					CreateAxis(m_pSelectedObject);
					if (input->IsMouseInsideObject(m_pAxis_X)|| input->IsMouseInsideObject(m_pAxis_Y))
					{
						m_bAxis_Actice = true;
					}
				}	
			}
			else if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT)
			{
				if (m_bAxis_Actice)
				{
					if(input->)
				}
			}
		}
	}
	else
	{
		if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (m_pAxis_X != nullptr && m_pAxis_Y != nullptr)
			{
				GameObjectManager::GetInstance()->DeleteObject("Axis_X");
				GameObjectManager::GetInstance()->DeleteObject("Axis_Y");
			}			
			m_bAxis_Actice = false;
		}
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
			m_pSelectedObject = input->IsMouseInsideObject(obj);
			if (m_pSelectedObject != nullptr)
			{
				std::cout << m_pSelectedObject->GetName() << std::endl;
				return;
			}			
			else
			{
				m_pSelectedObject = nullptr;
			}
		}		
	}	
}
