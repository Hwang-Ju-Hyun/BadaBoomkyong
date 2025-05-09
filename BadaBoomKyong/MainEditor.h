#pragma once
#include "Singleton.h"

#ifdef _DEBUG
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ImGuizmo.h>

#include <vector>
class BaseComponent;
class GameObject;
class Camera;
class Transform;

class MainEditor
{
public:
	SINGLETON(MainEditor);
private:
	GameObject* m_pSelectedObjByPannel=nullptr;	
	Transform* m_pTransform_SelectedObj = nullptr;
	Camera* m_pCam = nullptr;				
public:
	void Init();
	void Update();	
private:	
	void DeletObjectModal();
	void TopMenuBarDraw();
	void ObjectPannelDraw();	
	void DrawGizmo();
	void UpdateEditorCameraControls();

};
#endif