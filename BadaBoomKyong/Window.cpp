#include "Window.h"
#include <cassert>

Window::Window() {}

Window::~Window(){}

static float time = 0.f;

void Window::Init(GLint _windowWidth, GLint _windowHeight)
{
	m_iWindowWidth = _windowWidth;
	m_iWindowHeight = _windowHeight;

	m_pWindowHandle = glfwCreateWindow(m_iWindowWidth, m_iWindowHeight,m_cWindowTitleName, NULL, NULL);
	assert(m_pWindowHandle != nullptr);

	glfwMakeContextCurrent(m_pWindowHandle);

	glViewport(0,0, m_iWindowWidth, m_iWindowHeight);
}

void Window::Exit()
{
	glfwDestroyWindow(m_pWindowHandle);
}
