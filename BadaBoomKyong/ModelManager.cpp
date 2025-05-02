#include "ModelManager.h"
#include "Model.h"
#include <cassert>
#include <utility>

ModelManager::ModelManager()
{	
}

ModelManager::~ModelManager()
{	
	
}

Model* ModelManager::FindModel(MODEL_TYPE _modelType)
{
	auto models = GetAllModels();
	for (auto mdl : models)
	{
		if (mdl->GetModelType() == _modelType)
			return mdl;
	}	
	return nullptr;
}

void ModelManager::Init()
{
	LineInit();
	TriangleInit();
	RectangleInit();
	//PlaneInit();
	//CubeInit();
}

void ModelManager::Exit()
{
	size_t size = m_vModels.size();
	for (int i = 0;i < size;i++)
	{
		delete m_vModels[i];
		m_vModels[i] = nullptr;
	}
	m_vModels.clear();
	std::vector<Model*> temp;
	temp.swap(m_vModels);
}

void ModelManager::LineInit()
{
	std::string name = "Line";
	std::vector<Model::VertexAttribute> vertices =
	{
		{glm::vec3{ -0.5f, 0.f, 0.f }, glm::vec2{ 0.f, 0.f }},
		{glm::vec3{ 0.5f, 0.f, 0.f }, glm::vec2{ 0.f, 0.f }}
	};
	GLenum type = GL_LINES;
	Model* model = new Model(name, MODEL_TYPE::LINE, type, std::move(vertices));

	assert(model != nullptr);

	AddModel(model);
}

void ModelManager::TriangleInit()
{
	std::string name = "Triangle";	
	std::vector<Model::VertexAttribute> vertices =						
	{								
		{glm::vec3{ -0.5f, -0.5f, 0.f }, glm::vec2{ 0.f, 0.f }}, // Bottom Left
		{glm::vec3{  0.0f,  0.5f, 0.f }, glm::vec2{ 0.5f, 1.f }}, // Top Center
		{glm::vec3{  0.5f, -0.5f, 0.f }, glm::vec2{ 1.f, 0.f }}  // Bottom Right
	};							
	GLenum type = GL_TRIANGLES;		
	Model* model = new Model(name, MODEL_TYPE::TRIANGLE, type, std::move(vertices));
	
	assert(model != nullptr);

	AddModel(model); 
}

void ModelManager::RectangleInit()
{	
	std::string name = "Rectangle";
	std::vector<Model::VertexAttribute> vertices =
	{
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
	//todo
}
//
//void ModelManager::PlaneInit()
//{
//	std::string name = "Plane";
//	std::vector<Model::VertexAttribute> vertices =
//	{		
//		{glm::vec3{-0.5f,0.5f,0.f},glm::vec2{0.f,0.f}, glm::vec3{0.f,0.f,1.f}},//Top Left
//		{glm::vec3{-0.5f,-0.5f,0.f},glm::vec2{0.f,1.f},glm::vec3{0.f,0.f,1.f}},//Bottom left
//		{glm::vec3{0.5f,-0.5f,0.f},glm::vec2{1.f,0.f} ,glm::vec3{0.f,0.f,1.f}},//Bottom Right
//		{glm::vec3{0.5f,0.5f,0.f},glm::vec2{1.f,1.f}  ,glm::vec3{0.f,0.f,1.f}} //Top Right
//	};
//	std::vector<unsigned int> indices =
//	{
//		0,1,2,0,3,2
//	};
//	GLenum type = GL_TRIANGLES;
//	Model* model = new Model(name, MODEL_TYPE::PLANE, type, std::move(vertices), std::move(indices));
//
//	assert(model != nullptr);
//
//	AddModel(model);
//}
//
//void ModelManager::CubeInit()
//{
//	std::string name = "Cube";
//	std::vector<Model::VertexAttribute> vertices =
//	{
//		// Front face
//		{{-0.5f, -0.5f,  0.5f}, {0.f, 1.f}, {0.f, 0.f, 1.f}}, // 0
//		{{ 0.5f, -0.5f,  0.5f}, {1.f, 1.f}, {0.f, 0.f, 1.f}}, // 1
//		{{ 0.5f,  0.5f,  0.5f}, {1.f, 0.f}, {0.f, 0.f, 1.f}}, // 2
//		{{-0.5f,  0.5f,  0.5f}, {0.f, 0.f}, {0.f, 0.f, 1.f}}, // 3
//
//		// Back face
//		{{ 0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {0.f, 0.f, -1.f}}, // 4
//		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, 0.f, -1.f}}, // 5
//		{{-0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {0.f, 0.f, -1.f}}, // 6
//		{{ 0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {0.f, 0.f, -1.f}}, // 7
//
//		// Left face
//		{{-0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {-1.f, 0.f, 0.f}}, // 8
//		{{-0.5f, -0.5f,  0.5f}, {1.f, 1.f}, {-1.f, 0.f, 0.f}}, // 9
//		{{-0.5f,  0.5f,  0.5f}, {1.f, 0.f}, {-1.f, 0.f, 0.f}}, // 10
//		{{-0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {-1.f, 0.f, 0.f}}, // 11
//
//		// Right face
//		{{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f}, {1.f, 0.f, 0.f}}, // 12
//		{{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {1.f, 0.f, 0.f}}, // 13
//		{{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {1.f, 0.f, 0.f}}, // 14
//		{{ 0.5f,  0.5f,  0.5f}, {0.f, 0.f}, {1.f, 0.f, 0.f}}, // 15
//
//		// Top face
//		{{-0.5f,  0.5f,  0.5f}, {0.f, 1.f}, {0.f, 1.f, 0.f}}, // 16
//		{{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f}, {0.f, 1.f, 0.f}}, // 17
//		{{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {0.f, 1.f, 0.f}}, // 18
//		{{-0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {0.f, 1.f, 0.f}}, // 19
//
//		// Bottom face
//		{{-0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {0.f, -1.f, 0.f}}, // 20
//		{{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, -1.f, 0.f}}, // 21
//		{{ 0.5f, -0.5f,  0.5f}, {1.f, 0.f}, {0.f, -1.f, 0.f}}, // 22
//		{{-0.5f, -0.5f,  0.5f}, {0.f, 0.f}, {0.f, -1.f, 0.f}}, // 23
//	};
//
//	std::vector<unsigned int> indices =
//	{
//		// Front face
//		0, 1, 2, 0, 2, 3,
//		// Back face
//		4, 5, 6, 4, 6, 7,
//		// Left face
//		8, 9,10, 8,10,11,
//		// Right face
//		12,13,14,12,14,15,
//		// Top face
//		16,17,18,16,18,19,
//		// Bottom face
//		20,21,22,20,22,23
//	};
//
//	GLenum type = GL_TRIANGLES;
//	Model* model = new Model(name, MODEL_TYPE::CUBE, type, std::move(vertices), std::move(indices));
//
//	assert(model != nullptr);
//
//	AddModel(model);
//}
//
//
//
