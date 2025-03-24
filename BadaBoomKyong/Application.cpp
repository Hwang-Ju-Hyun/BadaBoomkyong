#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include "Window.h"

Application::Application(){}

Application::~Application(){}


void Application::Init()
{
    //GLFW Init
    int iGlfwInit_Err = glfwInit();
    assert(iGlfwInit_Err);

    //GLEW Init
    GLenum iGlewInit_Err = glewInit(); 
    assert(iGlewInit_Err>0);
    
    //Window Init
    const GLint iWindowWidth = Window::GetInstance()->GetWindowWidth();
    const GLint iWindowHeight = Window::GetInstance()->GetWindowHeight();
    Window::GetInstance()->Init(iWindowWidth, iWindowHeight);

    GLFWwindow* pWindowHandle = Window::GetInstance()->GetWindowHandle();

    //TODO : Make sure to implement InputManager(KeyCallBack, MouseCallBack)
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
