#pragma once
#include "Singleton.h"
#include <GLFW/glfw3.h>
class Window
{
public:
	SINGLETON(Window);
private:
	const char m_cWindowTitleName[100] = "BadaBoomKyoung";
	GLint m_iWindowWidth = 1980;
	GLint m_iWindowHeight = 1080;
	GLFWwindow* m_pWindowHandle = nullptr;
public:
	inline const char* GetWindowName() { return m_cWindowTitleName; }
	inline const GLint GetWindowWidth() { return m_iWindowWidth; }
	inline const GLint GetWindowHeight() { return m_iWindowHeight; }
	inline GLFWwindow* GetWindowHandle() { return m_pWindowHandle; }
public:
	void Init(GLint _windowWidth, GLint _windowHeight);
	void Exit();
};
