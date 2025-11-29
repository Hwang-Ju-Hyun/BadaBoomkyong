#pragma once
#include "Singleton.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>
#include <glm.hpp>

class GameObject;

static const int g_iKeySize = 42;

static int g_aKey[g_iKeySize] =
{
	GLFW_KEY_ESCAPE,
	GLFW_KEY_ENTER,
	GLFW_KEY_LEFT_ALT,
	GLFW_KEY_LEFT_CONTROL,
	GLFW_KEY_LEFT_SHIFT,
	GLFW_KEY_SPACE,
	GLFW_KEY_0,
	GLFW_KEY_1,
	GLFW_KEY_2,
	GLFW_KEY_3,
	GLFW_KEY_4,
	GLFW_KEY_5,
	GLFW_KEY_Q,
	GLFW_KEY_W,
	GLFW_KEY_E,
	GLFW_KEY_R,
	GLFW_KEY_T,
	GLFW_KEY_A,
	GLFW_KEY_S,
	GLFW_KEY_D,
	GLFW_KEY_F,
	GLFW_KEY_G,
	GLFW_KEY_Z,
	GLFW_KEY_X,
	GLFW_KEY_C,
	GLFW_KEY_V,
	GLFW_KEY_Y,
	GLFW_KEY_U,
	GLFW_KEY_I,
	GLFW_KEY_O,
	GLFW_KEY_P,
	GLFW_KEY_H,
	GLFW_KEY_J,
	GLFW_KEY_K,
	GLFW_KEY_L,
	GLFW_KEY_B,
	GLFW_KEY_N,
	GLFW_KEY_M,
	GLFW_KEY_UP,
	GLFW_KEY_DOWN,
	GLFW_KEY_LEFT,
	GLFW_KEY_RIGHT,
};

enum KEY_STATE
{
	NONE = -1,
	RELEASE=0,
	PRESS=1,
	HOLD=2,
};

struct KeyInfo
{
	bool bHeld = false;      // 현재 눌려 있는 상태 (콜백에서 설정됨)
	bool bPrevHeld = false;  // 이전 프레임 눌림 여부
	KEY_STATE eState = KEY_STATE::NONE; // 최종 Key 상태 (Update()에서 계산됨)
};

static const int g_iMouseBtnSize = 2;

static int g_aMouseBtn[g_iMouseBtnSize] =
{
	GLFW_MOUSE_BUTTON_LEFT,
	GLFW_MOUSE_BUTTON_RIGHT
};

enum MOUSE_STATE
{
	MOUSE_NONE=-1,
	MOUSE_RELEASE = 0,
	MOUSE_PRESS = 1,
	MOUSE_HOLD = 2,
};

struct MouseBtnInfo
{
	bool bHeld = false;
	bool bPrevHeld = false;
	MOUSE_STATE eState = MOUSE_STATE::MOUSE_NONE;
};

class InputManager
{
public:
	SINGLETON(InputManager);	
private:
	static std::unordered_map<int, KeyInfo> m_mKeyState;
	static std::unordered_map<int, MouseBtnInfo> m_mMouseBtnState;
	static glm::vec2 m_vCursorPosition;
public:
	void Init();
	void Update();		
public:
	static void CursorWorldPositionCallBack(GLFWwindow* _window, double _xpos, double _ypos);
	static void KeyboardCallBack(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	static void MouseButtonCallBack(GLFWwindow* _window, int _button, int _action, int _mods);
public:
	inline KEY_STATE GetKetCode(int _key){ return m_mKeyState[_key].eState; }
	inline MOUSE_STATE GetMouseBtn(int _btn) { return m_mMouseBtnState[_btn].eState; }
	inline glm::vec2 GetCursorPostion()const { return m_vCursorPosition; }
private:
	static glm::vec2 GetWolrdPosFromScreenPos(glm::vec2 _pos);
	void KeyboardInputUpdate();		
	void MouseBtnInputUpdate();
public:
	GameObject* IsMouseInsideObject(GameObject* _obj);
	void PrintCursorPosInConsole();
};

