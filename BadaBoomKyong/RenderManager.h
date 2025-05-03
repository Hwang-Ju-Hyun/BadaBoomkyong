#pragma once
#include "Singleton.h"
#include "header.h"
#include <vector>

class Shader;
class Camera;

//todo : 나중에 3d오브젝트 띄우고 다 되면 주석 다지우셈
class RenderManager
{
public:
	SINGLETON(RenderManager);
private:
	std::vector<Shader*> m_vShdr;
	//Shader* shdr = nullptr;
public:
	//inline void SetShader(Shader* _shdr) { shdr = _shdr; }
	inline Shader* GetShader(SHADER_REF _shdrRef) { return m_vShdr[int(_shdrRef)]; }
	//inline Shader* GetShader()const { return shdr; }
	Camera* m_pCam=nullptr;
public:
	void Init();
	void Draw();
	void Exit();
};

