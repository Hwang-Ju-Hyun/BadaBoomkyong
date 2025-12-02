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
#include "EventManager.h"
#include <string>
#include <sstream>
#include "UIManager.h"

#ifdef _DEBUG
#include <vld.h>
#endif
#include <Windows.h>
#ifdef _DEBUG
void main(void)
{		
	Application::GetInstance()->Init();	
	TimeManager::m_dDeltaTime = 0;
	TimeManager::m_dLastFrame= 0;
	static int update_cnt = 0;
	static int fps = 0;
	static float AccDT = 0.f;
	while (!glfwWindowShouldClose(Window::GetInstance()->GetWindowHandle()))
	{
		float CurrentTime = glfwGetTime();
		TimeManager::m_dDeltaTime = CurrentTime - TimeManager::m_dLastFrame;
		TimeManager::m_dLastFrame = CurrentTime;		

		Application::GetInstance()->Update();

		RenderManager::GetInstance()->Draw();
        UIManager::GetInstance()->Render();

		//Event
		EventManager::GetInstance()->Update();

		update_cnt++;
		AccDT += TimeManager::m_dDeltaTime;
		if (AccDT >= 1.f)
		{
			std::ostringstream outs;
			outs.precision(2);
			outs << std::fixed
				<< "MyGame - FPS: " << fps;

			glfwSetWindowTitle(Window::GetInstance()->GetWindowHandle(), outs.str().c_str());
			fps = update_cnt;
			update_cnt = 0;
			AccDT = 0.f;			
		}		
	}	
	Application::GetInstance()->Exit();
	return ;
}
#endif



int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    Application::GetInstance()->Init();
    TimeManager::m_dDeltaTime = 0;
    TimeManager::m_dLastFrame = 0;
    static int update_cnt = 0;
    static int fps = 0;
    static float AccDT = 0.f;

    while (!glfwWindowShouldClose(Window::GetInstance()->GetWindowHandle()))
    {
        float CurrentTime = glfwGetTime();
        TimeManager::m_dDeltaTime = CurrentTime - TimeManager::m_dLastFrame;
        TimeManager::m_dLastFrame = CurrentTime;

        Application::GetInstance()->Update();
        RenderManager::GetInstance()->Draw();
        EventManager::GetInstance()->Update();

        update_cnt++;
        AccDT += TimeManager::m_dDeltaTime;
        if (AccDT >= 1.f)
        {
            std::ostringstream outs;
            outs.precision(2);
            outs << std::fixed
                << "MyGame - FPS: " << fps;

            glfwSetWindowTitle(Window::GetInstance()->GetWindowHandle(), outs.str().c_str());
            fps = update_cnt;
            update_cnt = 0;
            AccDT = 0.f;
        }
        std::cout << fps << std::endl;
    }

    Application::GetInstance()->Exit();
    return 0;
}
