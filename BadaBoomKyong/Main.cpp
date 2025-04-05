#include <iostream>
#include "Application.h"
#include "Singleton.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "RenderManager.h"
#include "ComponentManager.h"
#include "ModelManager.h"
#include "GameObjectManager.h"
#include <vld.h>

int main(void)
{			
	
	Application::GetInstance()->Init();	

	while (!glfwWindowShouldClose(Window::GetInstance()->GetWindowHandle()))
	{
		Application::GetInstance()->Update();
		RenderManager::GetInstance()->Draw();
	}	
	Application::GetInstance()->Exit();
	return 0;
}