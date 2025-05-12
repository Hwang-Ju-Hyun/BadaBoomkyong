#pragma once
#include "Singleton.h"
#include "header.h"
#include <vector>

class Shader;
class Camera;
class FrameBuffer;

class RenderManager
{
public:
	SINGLETON(RenderManager);
private:
	std::vector<Shader*> m_vShdr;
public:	
	inline Shader* GetShader(SHADER_REF _shdrRef) { return m_vShdr[int(_shdrRef)]; }	
	Camera* m_pCam=nullptr;
public:
	void Init();
	void Draw();
	void Exit();
public:
	inline Camera* GetCamera()const { return m_pCam; }
private:
	FrameBuffer* m_pFrameBuffer = nullptr;
};

