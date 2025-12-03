#include "InputManager.h"
#include "Window.h"
#include "GameObject.h"
#include "Transform.h"
#include "GeometryUtill.h"
#include <iostream>

InputManager::InputManager() {}
InputManager::~InputManager() {}

std::unordered_map<int, KeyInfo> InputManager::m_mKeyState = {};
std::unordered_map<int, MouseBtnInfo> InputManager::m_mMouseBtnState = {};
glm::vec2 InputManager::m_vCursorPosition = {};


void InputManager::CursorWorldPositionCallBack(GLFWwindow* _window, double _xpos, double _ypos)
{
    
    m_vCursorPosition = GetWolrdPosFromScreenPos(glm::vec2{ _xpos,_ypos});   
}

void InputManager::KeyboardCallBack(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    if (_action == GLFW_PRESS || _action == GLFW_REPEAT)
    {
        m_mKeyState[_key].bHeld = true;
    }
    else if (_action == GLFW_RELEASE)
    {
        m_mKeyState[_key].bHeld = false;
    }
}

void InputManager::MouseButtonCallBack(GLFWwindow* _window, int _button, int _action, int _mods)
{
    if (_action == GLFW_PRESS || _action == GLFW_REPEAT)
    {
        m_mMouseBtnState[_button].bHeld = true;
    }
    else if (_action == GLFW_RELEASE)
    {
        m_mMouseBtnState[_button].bHeld = false;
    }
}

void InputManager::KeyboardInputUpdate()
{
    for (auto iter = m_mKeyState.begin(); iter != m_mKeyState.end(); iter++)
    {
        int key = iter->first;
        KeyInfo& info = iter->second;

        info.eState = NONE;

        if (!info.bPrevHeld && info.bHeld)
        {
            info.eState = PRESS;
        }
        else if (info.bPrevHeld && info.bHeld)
        {
            info.eState = HOLD;
        }
        else if (info.bPrevHeld && !info.bHeld)
        {
            info.eState = RELEASE;
        }

        info.bPrevHeld = info.bHeld;
    }
}

void InputManager::MouseBtnInputUpdate()
{
    for (auto iter = m_mMouseBtnState.begin(); iter != m_mMouseBtnState.end(); iter++)
    {
        int key = iter->first;
        MouseBtnInfo& info = iter->second;

        info.eState = MOUSE_STATE::MOUSE_NONE;

        if (!info.bPrevHeld && info.bHeld)
        {
            info.eState = MOUSE_STATE::MOUSE_PRESS;
        }
        else if (info.bPrevHeld && info.bHeld)
        {
            info.eState = MOUSE_STATE::MOUSE_HOLD;
        }
        else if (info.bPrevHeld && !info.bHeld)
        {
            info.eState = MOUSE_STATE::MOUSE_RELEASE;
        }
        info.bPrevHeld = info.bHeld;
    }
}

GameObject* InputManager::IsMouseInsideObject(GameObject* _obj)
{
    if (_obj->GetModel()!=nullptr)
    {
        glm::vec2 cur_pos = GetCursorPostion();
        
        Transform* obj_trs = dynamic_cast<Transform*>(_obj->FindComponent(Transform::TransformTypeName));        
        GameObject* obj = nullptr;
        if (obj_trs != nullptr)
        {
            if (_obj->GetModelType() == MODEL_TYPE::TRIANGLE)
            {//todo 이거 지우던가 하던가 하셈 model
                //GeometryUtil::GetInstance()->IsPointInsideTraingle(cur_pos, obj_trs) ? obj = _obj : obj = nullptr;
            }
            else if (_obj->GetModelType() == MODEL_TYPE::RECTANGLE)
            {
                GeometryUtil::GetInstance()->IsPointInsideRectangle(cur_pos, obj_trs) ? obj = _obj : obj = nullptr;
            }
            else if(_obj->GetModelType()==MODEL_TYPE::LINE)
            {
                GeometryUtil::GetInstance()->IsPointInsideRectangle(cur_pos, obj_trs) ? obj = _obj : obj = nullptr;
            }
            return obj;
        }                
    }
    return nullptr;
}

void InputManager::PrintCursorPosInConsole()
{
    std::cout << m_vCursorPosition.x << " , " << m_vCursorPosition.y << std::endl;
}


void InputManager::Init()
{
    for (int i = 0; i < g_iKeySize; i++)
    {
        m_mKeyState[g_aKey[i]] = {};
    }
    for (int i = 0;i < g_iMouseBtnSize;i++)
    {
        m_mMouseBtnState[g_aMouseBtn[i]] = {};
    }

    glfwSetKeyCallback(Window::GetInstance()->GetWindowHandle(), KeyboardCallBack);
    glfwSetCursorPosCallback(Window::GetInstance()->GetWindowHandle(), CursorWorldPositionCallBack);    
    glfwSetMouseButtonCallback(Window::GetInstance()->GetWindowHandle(), MouseButtonCallBack);
}
void InputManager::Update()
{
    KeyboardInputUpdate();
    MouseBtnInputUpdate();

}

glm::vec2 InputManager::GetWolrdPosFromScreenPos(glm::vec2 _pos)
{
    GLint window_width=Window::GetInstance()->GetWindowWidth();
    GLint window_height=Window::GetInstance()->GetWindowHeight();

    int pos_x = _pos.x;
    int pos_y = _pos.y;    

    glm::vec2 world_pos = { pos_x - (window_width / 2),(pos_y - (window_height / 2))*-1 };    
    return world_pos;
}
