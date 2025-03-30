#include "ModelManager.h"
#include "Model.h"
#include <cassert>

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{	
	int size = m_vModels.size();
	for (int i = 0;i < size;i++)
	{
		delete m_vModels[i];
		m_vModels[i] = nullptr;
	}
}

void ModelManager::AddModel(Model* _model)
{
	m_vModels.push_back(_model);
}

void ModelManager::Init()
{
}

void ModelManager::TriangleInit()
{
	std::string name = "Triangle";
	std::vector<Model::VertexAttribute> vertices;
	vertices =
	{		
		{glm::vec3{-1.f,-1.f,0.f},		glm::vec3{0.f,0.f,0.f}},//Bottom Left
		{glm::vec3{0.f,1.f,0.f},		glm::vec3{0.5f,1.f,0.f}},//Middle 
		{glm::vec3{1.f,-1.f,0.f},		glm::vec3{1.f,0.f,0.f}},//Bottom Right		
	};

	GLenum type = GL_TRIANGLES;	
	Model* model = new Model(name, MODEL_TYPE::TRIAGNLE, type, vertices);
	
	assert(model != nullptr);

	AddModel(model);
}

void ModelManager::CircleInit()
{
}

void ModelManager::RectangleInit()
{
}