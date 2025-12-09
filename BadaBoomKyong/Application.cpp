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
#include "Stage02.h"
#include "StageTest.h"
#include "UIManager.h"
#include "TimeManager.h"
#include "TextManager.h"
#include "AudioManager.h"

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

    AudioManager::GetInstance()->Init();

    //ModelInit
    ModelManager::GetInstance()->Init();                        

    //GameStateManager
    BaseLevel* lvl_01=GameStateManager::GetInstance()->FindLevel(STAGE_TYPE::GAME_START);
    GameStateManager::GetInstance()->ChangeLevel(lvl_01);

    //FactoryManager::GetInstance()->Init();

    //ComponentInit
    ComponentManager::GetInstance()->Init();
    
    //InputManager
    InputManager::GetInstance()->Init();                    

    //RenderInit            
    RenderManager::GetInstance()->Init();
    RenderManager::GetInstance()->InitDebugLineShader();
  
    UIManager::GetInstance()->Init();
#ifdef _DEBUG
    //MainEditor
    MainEditor::GetInstance()->Init();
#endif    

    TextManager::GetInstance()->Init("../Extern/Assets/Fonts/COOPBL.TTF",48, Window::GetInstance()->GetWindowWidth(), Window::GetInstance()->GetWindowHeight());     
}
#include <iostream>
#include "GameStateManager.h"
void Application::Update()
{    
    glClearColor(0.f,0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    auto handle = Window::GetInstance()->GetWindowHandle();
    float dt = TimeManager::GetInstance()->GetDeltaTime();
   
    //Active
    GameObjectManager::GetInstance()->Awake();

    //GameState
    GameStateManager::GetInstance()->Update();    

    //GameObject
    GameObjectManager::GetInstance()->Update();    

    //Input
    InputManager::GetInstance()->Update();    

    //Collision
    CollisionManager::GetInstance()->Update();

    //UI
    UIManager::GetInstance()->Update(dt);

#ifdef _DEBUG
    //Main Editor    
    if (EventManager::GetInstance()->FindEvent(EVENT_TYPE::LEVEL_CHANGE) != EVENT_TYPE::LEVEL_CHANGE)
    {
        MainEditor::GetInstance()->Update();
    }
    
#endif        

    //Audio
    AudioManager::GetInstance()->Update();
}


void Application::Exit()
{
    GameStateManager::GetInstance()->ChangeLevel(nullptr);
    GameObjectManager::GetInstance()->Exit(); 
    ComponentManager::GetInstance()->Exit();
    ObjectPoolManager::GetInstance()->Exit();    
    FactoryManager::GetInstance()->Exit();
    ModelManager::GetInstance()->Exit();    
    UIManager::GetInstance()->Exit();
    ResourceManager::GetInstance()->RemoveAllRes();
    RenderManager::GetInstance()->Exit();
    AudioManager::GetInstance()->Exit();
    Window::GetInstance()->Exit();    
//#ifdef _DEBUG
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//#endif // DEBUG	
    glfwTerminate();
}
