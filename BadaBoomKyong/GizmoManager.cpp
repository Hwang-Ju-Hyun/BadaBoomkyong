#include "GizmoManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Transform.h"
#include "GameObject.h"
#include <iostream>

GizmoManager::GizmoManager()
{

}

GizmoManager::~GizmoManager()
{


}
void GizmoManager::Init()
{

}

void GizmoManager::Update()
{	
	UpdateSelectedObject();
	MoveObject();
}

void GizmoManager::Exit()
{
}

void GizmoManager::MoveObject()
{
	auto input = InputManager::GetInstance();
	if (m_pSelectedObject != nullptr)
	{		
		Transform* trs = dynamic_cast<Transform*>(m_pSelectedObject->FindComponent(Transform::TransformTypeName));
		if (trs != nullptr)
		{
			if (input->GetMouseBtn(GLFW_MOUSE_BUTTON_LEFT) == GLFW_REPEAT)
			{
				glm::vec2 pos = input->GetCursorPostion();
				trs->SetPosition({ pos,0.f });
			}
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
