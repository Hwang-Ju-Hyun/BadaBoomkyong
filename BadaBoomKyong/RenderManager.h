#pragma once
#include "Singleton.h"

class Shader;

class RenderManager
{
public:
	SINGLETON(RenderManager);
private:

	Shader* shdr = nullptr;
public:
	inline void SetShader(Shader* _shdr) { shdr = _shdr; }
	inline Shader* GetShader()const { return shdr; }
public:
	void Init();
	void Draw();
	void Exit();
};

