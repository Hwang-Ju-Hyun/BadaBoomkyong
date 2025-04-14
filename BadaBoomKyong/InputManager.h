#pragma once
#include "Singleton.h"
#include <GLFW/glfw3.h>
#include <vector>
#include <unordered_map>

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
	KEY_STATE eState = NONE; // 최종 Key 상태 (Update()에서 계산됨)
};

class InputManager
{
public:
	SINGLETON(InputManager);	
private:
	static std::unordered_map<int, KeyInfo> m_mKeyState;
public:
	void Init();
	void Update();
	KEY_STATE GetKetCode(int _key);
public:
	static void KeyCallBack(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};

