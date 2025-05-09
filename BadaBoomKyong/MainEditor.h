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
class FrameBuffer;
class MainEditor
{
public:
	SINGLETON(MainEditor);
private:
	GameObject* m_pSelectedObjByButton=nullptr;
	GameObject* m_pSelectedObjByLevel = nullptr;
	Transform* m_pTransform_SelectedObj_Level = nullptr;	
	Camera* m_pCam = nullptr;		
	FrameBuffer* m_pFrameBuffer = nullptr;
public:
	void Init();
	void Update();
	void Exit();
private:
	void FrameBufferDraw();
	void UpdateSelectedObjectByLevel();
	void TopMenuBarDraw();
	void ObjectPannelDraw();	
	void DrawGizmo(glm::mat4& _modelMatrix, const glm::mat4& _viewMatrix, const glm::mat4& _projectionMatrix);
 
};
#endif