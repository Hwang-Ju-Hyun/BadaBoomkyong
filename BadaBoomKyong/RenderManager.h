#pragma once
#include <glm.hpp>
#include "Singleton.h"
#include "header.h"
#include <vector>
#include "ParticleSystem.h"

class Shader;
class Camera;
class FrameBuffer;
class GameObject;
class Light;

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
	void InitDebugLineShader(); 
private:
	std::vector<Shader*> m_vShdr;
	std::vector<GameObject*> m_vTransParnetObject;
	std::vector<GameObject*> m_vOpaqueObject;
private:
	GLint m_iMVP_Location;
	GLint m_iUV_Offset_Location;
	GLint m_iUV_Scale_Location;
	GLint m_iHas_texture_location;
	GLint m_iOut_texture_location;
	GLint m_iHurtEffect_location;
	GLint m_iM2W_Location;
	GLint m_iLightNumber;
	GLint m_iLightColorOn;
	GLint m_iCamreaPosition;
	GLint m_iLightAffect_location;
	GLint m_iFogColor_location;
	GLint m_iFogStart_location;
	GLint m_iFogEnd_location;
	GLint m_iFogOn_location;
public:	
	inline Shader* GetShader(SHADER_REF _shdrRef) { return m_vShdr[int(_shdrRef)]; }	
	Camera* m_pCam=nullptr;
	Light* m_pLight=nullptr;		
public:
	void Init();
	void BeforeDraw();
	void Draw();
	void EndDraw();
	void Exit();
private:
	void DrawFog(GLint _shdrHandle,bool _fogOn);
	void DrawSkyBox(Camera* _cam);
private:
	void RenderOpaqueObject();
	void RenderTransParentObject();
public:
	const glm::mat4 GetMVP_ByObject(const GameObject& _obj);
public:
	inline Camera* GetCamera()const { return m_pCam; }
private:
	FrameBuffer* m_pFrameBuffer = nullptr;
public:
	Shader* debugLineShader = nullptr;
public:
	//todo : �� �����ϼ� ��ƼŬ ��������
	ParticleSystem* m_pParticleSystem = nullptr;

};