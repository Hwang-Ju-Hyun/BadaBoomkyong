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
    BaseLevel* lvl_01=GameStateManager::GetInstance()->FindLevel(STAGE_TYPE::STAGE_02);
    GameStateManager::GetInstance()->ChangeLevel(lvl_01);

    FactoryManager::GetInstance()->Init();


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
    //MainEditor::GetInstance()->Update();
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
    
    Window::GetInstance()->Exit();
    glfwTerminate();
}
