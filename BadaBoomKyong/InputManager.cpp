#include "InputManager.h"
#include "Window.h"
#include <iostream>

InputManager::InputManager() {}
InputManager::~InputManager() {}

std::unordered_map<int, KeyInfo> InputManager::m_mKeyState = {};

void InputManager::KeyCallBack(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
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


void InputManager::Init()
{
    for (int i = 0; i < g_iKeySize; i++)
    {
        m_mKeyState[g_aKey[i]] = {};
    }

    glfwSetKeyCallback(Window::GetInstance()->GetWindowHandle(), KeyCallBack);
}
void InputManager::Update()
{
    for (auto it = m_mKeyState.begin(); it != m_mKeyState.end(); ++it)
    {
        int key = it->first;
        KeyInfo& info = it->second;
        
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

KEY_STATE InputManager::GetKetCode(int _key)
{
    return m_mKeyState[_key].eState;
}