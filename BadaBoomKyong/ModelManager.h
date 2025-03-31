#pragma once
#include "Singleton.h"
#include <vector>

class Model;

class ModelManager
{
public:
	SINGLETON(ModelManager);
private:
	std::vector<Model*> m_vModels;
public:
	inline void AddModel(Model* _model){ m_vModels.push_back(_model); }
	inline std::vector<Model*> GetAllModels() { return m_vModels; }
public:
	void Init();
private:
	void TriangleInit();
	void CircleInit();
	void RectangleInit();	
};