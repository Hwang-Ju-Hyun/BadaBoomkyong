#pragma once
#include "Singleton.h"
#include <vector>

class UICanvas;
class Shader;
class Camera;

class UIManager
{
public:
	SINGLETON(UIManager);
public:
	std::vector<UICanvas*> m_vecCanvases;
	Shader* m_vShdr;
	Camera* m_pCam;
public:
	inline void AddCanvas(UICanvas* _canvas) { m_vecCanvases.push_back(_canvas); }
public:
	void Init();
	void Update(float _dt);
	void Render();
	void Exit();
};

