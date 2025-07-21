#pragma once
#include <glm.hpp>
#include "Singleton.h"
#include "header.h"
#include <vector>

class Shader;
class Camera;
class FrameBuffer;
class GameObject;

class RenderManager
{
public:
	SINGLETON(RenderManager);
private:
	//todo :�̰� ���� ���̴� �����ϱ�
	Shader* m_debugLineShader = nullptr; 
public:
	//todo :�̰� ���� ���̴� �����ϱ�
	GLuint GetDebugLineShader() const;
	void InitDebugLineShader(); // 
private:
	std::vector<Shader*> m_vShdr;
	std::vector<GameObject*> m_vTransParnetObject;
	std::vector<GameObject*> m_vOpaqueObject;
public:	
	inline Shader* GetShader(SHADER_REF _shdrRef) { return m_vShdr[int(_shdrRef)]; }	
	Camera* m_pCam=nullptr;
public:
	void Init();
	void BeforeDraw();
	void Draw();
	void EndDraw();
	void Exit();
private:
	void RenderOpaqueObject();
	void RenderTransParentObject();
public:
	const glm::mat4 GetMVP_ByObject(const GameObject& _obj);
public:
	inline Camera* GetCamera()const { return m_pCam; }
private:
	FrameBuffer* m_pFrameBuffer = nullptr;
};

