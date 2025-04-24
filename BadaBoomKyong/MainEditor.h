#pragma once
#include "Singleton.h"

#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <vector>
class BaseComponent;
class GameObject;

class MainEditor
{
public:
	SINGLETON(MainEditor);
private:
	GameObject* m_pSelectedObjByButton=nullptr;
	const char* m_sCreateObject_PopUp_Title = "CreateObject";
public:
	void Init();
	void Update();
private:  	
	void TopMenuBarDraw();
	void ObjectPannelDraw();
	void Draw_ObjectInfoPannel();
	//void Object
};
#endif