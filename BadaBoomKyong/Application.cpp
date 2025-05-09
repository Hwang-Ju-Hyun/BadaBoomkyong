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
    
    //InputManager
    InputManager::GetInstance()->Init();    

    //RenderInit            
    RenderManager::GetInstance()->Init();


#ifdef _DEBUG
    //MainEditor
    MainEditor::GetInstance()->Init();
#endif
}

void Application::Update()
{    
    glClearColor(0.f,0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    auto handle = Window::GetInstance()->GetWindowHandle();    

    //GameState
    GameStateManager::GetInstance()->Update();    

    //Input
    InputManager::GetInstance()->Update();

    //Component
    ComponentManager::GetInstance()->Update();

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
    ModelManager::GetInstance()->Exit();
    MainEditor::GetInstance()->Exit();
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
