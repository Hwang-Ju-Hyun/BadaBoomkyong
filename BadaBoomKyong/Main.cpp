#include <iostream>
#include "Application.h"
#include "Singleton.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "RenderManager.h"

int main(void)
{	
	Application::GetInstance()->Init();

	while (!glfwWindowShouldClose(Window::GetInstance()->GetWindowHandle()))
	{
		Application::GetInstance()->Update();
		RenderManager::GetInstance()->Draw();
	}
	
	return 0;
}