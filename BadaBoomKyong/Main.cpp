#include <iostream>
#include "Application.h"
#include "Singleton.h"
#include <GLFW/glfw3.h>
#include "Window.h"
#include "RenderManager.h"
#include "ComponentManager.h"
#include "ModelManager.h"
#include "GameObjectManager.h"
#include "TimeManager.h"
#ifdef _DEBUG
#include <vld.h>
#endif

int main(void)
{				
	Application::GetInstance()->Init();	
	TimeManager::m_dDeltaTime = 0;
	TimeManager::m_dLastFrame= 0;
	while (!glfwWindowShouldClose(Window::GetInstance()->GetWindowHandle()))
	{
		float CurrentTime = glfwGetTime();
		TimeManager::m_dDeltaTime = CurrentTime - TimeManager::m_dLastFrame;
		TimeManager::m_dLastFrame = CurrentTime;

		Application::GetInstance()->Update();
		RenderManager::GetInstance()->Draw();		
	}	
	Application::GetInstance()->Exit();
	return 0;
}
