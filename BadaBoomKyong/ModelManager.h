#pragma once
#include "Singleton.h"
#include <vector>

class Model;

class ModelManager
{
public:
	SINGLETON(ModelManager);
private:
	std::vector<Model> m_vModel;
public:
	void AddModel(const Model& _model);
public:
	void Init();
private:
	void TriangleInit();
	void CircleInit();
	void RectangleInit();
};