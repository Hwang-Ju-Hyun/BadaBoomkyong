#pragma once
#include "Singleton.h"

class GameObject;

class GizmoManager
{
public:
	SINGLETON(GizmoManager)
	
private:
	GameObject* m_pSelectedObject = nullptr;
public:
	void Init();
	void Update();
	void Exit();
public:
	void MoveObject();
	void UpdateSelectedObject();
};

