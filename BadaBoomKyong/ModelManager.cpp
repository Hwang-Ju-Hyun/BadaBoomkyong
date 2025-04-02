#include "ModelManager.h"
#include "Model.h"
#include <cassert>
#include <utility>

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

void ModelManager::Init()
{
	TriangleInit();
	RectangleInit();
}

void ModelManager::TriangleInit()
{
	std::string name = "Triangle";	
	std::vector<Model::VertexAttribute> vertices =						
	{								
		{glm::vec3{-1.f,-1.f,0.f},		glm::vec2{0.f,0.f}},//Bottom Left
		{glm::vec3{0.f,1.f,0.f},		glm::vec2{0.5f,1.f}},//Middle 
		{glm::vec3{1.f,-1.f,0.f},		glm::vec2{1.f,0.f}},//Bottom Right		
	};							
	GLenum type = GL_TRIANGLES;		
	Model* model = new Model(name, MODEL_TYPE::TRIAGNLE, type, std::move(vertices));
	
	assert(model != nullptr);

	AddModel(model); 
}

void ModelManager::RectangleInit()
{	
	std::string name = "Rectangle";
	std::vector<Model::VertexAttribute> vertices =
	{
		//{glm::vec3{-1.f,-1.f,0.f},glm::vec2{0.f,0.f}},//Bottom Left
		//{glm::vec3{-1.f,1.f,0.f},glm::vec2{0.f,1.f}},//Top Left
		//{glm::vec3{1.f,-1.f,0.f},glm::vec2{1.f,0.f}},//Bottom Right
		//{glm::vec3{1.f,1.f,0.f},glm::vec2{1.f,1.f}}//Top Right

		{glm::vec3{-0.5f,-0.5f,0.f},glm::vec2{0.f,0.f}},//Bottom Left
		{glm::vec3{-0.5f,0.5f,0.f},glm::vec2{0.f,1.f}},//Top Left
		{glm::vec3{0.5f,-0.5f,0.f},glm::vec2{1.f,0.f}},//Bottom Right
		{glm::vec3{0.5f,0.5f,0.f},glm::vec2{1.f,1.f}}//Top Right
	};
	std::vector<unsigned int> indices =
	{
		0,1,2,2,1,3
	};
	GLenum type = GL_TRIANGLES;
	Model* model = new Model(name, MODEL_TYPE::RECTANGLE, type, std::move(vertices),std::move(indices));

	assert(model != nullptr);

	AddModel(model);
}

void ModelManager::CircleInit()
{
}

