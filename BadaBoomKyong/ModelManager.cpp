#include "ModelManager.h"
#include "Model.h"

ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{

}

void ModelManager::AddModel(const Model& _model)
{
	m_vModel.push_back(_model);
}

void ModelManager::Init()
{
}

void ModelManager::TriangleInit()
{
}

void ModelManager::CircleInit()
{
}

void ModelManager::RectangleInit()
{
}
