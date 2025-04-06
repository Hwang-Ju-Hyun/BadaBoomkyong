#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include "Window.h"
#include "GameStateManager.h"
#include "Stage01.h"
#include "ModelManager.h"
#include "Shader.h"
#include "RenderManager.h"
#include "ComponentManager.h"
#include "GameObjectManager.h"

Application::Application(){}

Application::~Application(){}


void Application::Init()
{
    //GLFW Init
    int iGlfwInit_Err = glfwInit();
    assert(iGlfwInit_Err);

    //Window Init        
    Window::GetInstance()->Init(Window::GetInstance()->GetWindowWidth(), Window::GetInstance()->GetWindowHeight());

    //GLEW Init
    GLenum iGlewInit_Err = glewInit(); 
    assert(iGlewInit_Err == GLEW_OK);        
    
    //ModelInit
    ModelManager::GetInstance()->Init();
    
    //RenderInit            
    RenderManager::GetInstance()->Init();
   
    //GameStateManager    
    GameStateManager::GetInstance()->ChangeLevel(new Stage01("Stage01"));
        

    //TODO : Make sure to implement InputManager(KeyCallBack, MouseCallBack)
    //GLFWwindow* pWindowHandle = Window::GetInstance()->GetWindowHandle();
    //glfwSetKeyCallback(pWindowHandle,KeyCallBack)
    //glfwSetMouseButtonCallback(pWindowHandle, MouseCallBack);
    //glfwSetCursorPosCallback(pWindowHandle, MousePositionCallBack);
}

void Application::Update()
{    
    glClearColor(0.f,0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    auto handle = Window::GetInstance()->GetWindowHandle();    

    //GameState
    GameStateManager::GetInstance()->Update();    

    //Component
    ComponentManager::GetInstance()->Update();
}

void Application::Exit()
{
    GameStateManager::GetInstance()->ChangeLevel(nullptr);
    ComponentManager::GetInstance()->Exit();
    GameObjectManager::GetInstance()->Exit();
    ModelManager::GetInstance()->Exit();
    RenderManager::GetInstance()->Exit();
    Window::GetInstance()->Exit();
    glfwTerminate();
}
