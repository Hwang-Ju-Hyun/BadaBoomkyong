#pragma once
#include "Singleton.h"

class GameObject;

class GizmoManager
{
public:
	SINGLETON(GizmoManager)
	
private:
	GameObject* m_pSelectedObject = nullptr;
	GameObject* m_pAxis_X=nullptr;
	GameObject* m_pAxis_Y=nullptr;
private:
	bool m_bGizmoActive = false;
public:
	void Init();
	void Update();
	void Exit();
public:
	void CreateAxis(GameObject* _obj);
public:
	void MoveObject();
	void UpdateSelectedObject();
	
};