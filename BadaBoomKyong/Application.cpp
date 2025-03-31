#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include "Window.h"
#include "ModelManager.h"
#include "Shader.h"
#include "RenderManager.h"

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
    


    //TODO : Make sure to implement InputManager(KeyCallBack, MouseCallBack)
    //GLFWwindow* pWindowHandle = Window::GetInstance()->GetWindowHandle();
    //glfwSetKeyCallback(pWindowHandle,KeyCallBack)
    //glfwSetMouseButtonCallback(pWindowHandle, MouseCallBack);
    //glfwSetCursorPosCallback(pWindowHandle, MousePositionCallBack);
}

void Application::Update()
{
    Window::GetInstance()->Update();
    
}

void Application::Exit()
{
    glfwTerminate();
}
