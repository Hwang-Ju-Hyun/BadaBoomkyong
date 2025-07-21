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
#include "InputManager.h"
#include "MainEditor.h"
#include "CollisionManager.h"
#include "FactoryManager.h"
#include "BulletFactory.h"
#include "Bullet.h"
#include "ObjectPoolManager.h"
#include "EventManager.h"
#include "ResourceManager.h"

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

    //GameStateManager    
    GameStateManager::GetInstance()->ChangeLevel(new Stage01("Stage01"));

    //FactoryManager    
    FactoryManager::GetInstance()->Init();

    //ComponentInit
    ComponentManager::GetInstance()->Init();       

    
    //InputManager
    InputManager::GetInstance()->Init();                

    //RenderInit            
    RenderManager::GetInstance()->Init();
    RenderManager::GetInstance()->InitDebugLineShader();
  
#ifdef _DEBUG
    //MainEditor
    MainEditor::GetInstance()->Init();
#endif    
}
#include <iostream>
void Application::Update()
{    
    glClearColor(0.f,0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    auto handle = Window::GetInstance()->GetWindowHandle();

    //GameObjectManager
    //GameObjectManager::GetInstance()->Update();
    
    //Active
    ComponentManager::GetInstance()->Awake();

    //GameState
    GameStateManager::GetInstance()->Update();    

    //Component
    ComponentManager::GetInstance()->Update();

    //Input
    InputManager::GetInstance()->Update();    

    //Collision
    CollisionManager::GetInstance()->Update();

#ifdef _DEBUG
    //Main Editor
    MainEditor::GetInstance()->Update();
#endif    
}

void Application::Exit()
{        
    GameStateManager::GetInstance()->ChangeLevel(nullptr);
    ComponentManager::GetInstance()->Exit();
    GameObjectManager::GetInstance()->Exit(); 
    ResourceManager::GetInstance()->RemoveAllRes();
    ModelManager::GetInstance()->Exit();    
    FactoryManager::GetInstance()->Exit();
    ObjectPoolManager::GetInstance()->Exit();
    RenderManager::GetInstance()->Exit();
    
#ifdef _DEBUG
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
#endif // DEBUG
    Window::GetInstance()->Exit();
    glfwTerminate();
}
