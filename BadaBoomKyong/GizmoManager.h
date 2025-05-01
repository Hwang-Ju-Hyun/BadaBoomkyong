#pragma once
#include "Singleton.h"
#include <glm.hpp>
#ifndef _GIZMO
class GameObject;

struct SelectObjectInfo
{
	GameObject* s_pCurSelectedObject = nullptr;
	bool s_bIsSelected = false;
};

class GizmoManager
{
public:
	SINGLETON(GizmoManager)
	
private:
	GameObject* m_pPrevSelectedObject = nullptr;
	GameObject* m_pCurSelectedObject = nullptr;
	GameObject* m_pAxis_X=nullptr;
	GameObject* m_pAxis_Y=nullptr;		
private:
	bool m_bIsAxis_Selected = false;
	bool m_bAxis_Actice_X = false;
	bool m_bAxis_Actice_Y = false;
	glm::vec3 m_vAxisScale = { 100.f,10.f,1.f };
public:
	//void Init();
	//void Update();
	//void Exit();
public:
	static constexpr const char* Axis_X_Name = "Axis_X";
	static constexpr const char* Axis_Y_Name = "Axis_Y";
public:	
	void MoveObject();
	void UpdateSelectedObject();
private:
	void Delete_Axis_And_Reset();
	void CreateAxis(GameObject* _obj);
};
#endif
