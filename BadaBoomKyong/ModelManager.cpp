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
	PlaneInit();
	CubeInit();
	//todo : load 이거 이상함
	LoadModel("tempShip.obj");
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
		{glm::vec3{-0.5f,-0.5f,0.f},glm::vec2{0.f,1.f}},//Top Left
		{glm::vec3{0.5f,-0.5f,0.f},glm::vec2{1.f,1.f}},//Bottom Right
		{glm::vec3{0.5f,0.5f,0.f},glm::vec2{1.f,0.f}},//Top Right
		{glm::vec3{-0.5f,0.5f,0.f},glm::vec2{0.f,0.f}}//Bottom left
	};
	std::vector<unsigned int> indices =
	{
		0,1,2,0,2,3
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

void ModelManager::PlaneInit()
{
	std::string name = "Plane";
	std::vector<Model::VertexAttribute> vertices =
	{		
		//			VERTEX				UV					NORMAL
		{glm::vec3{-0.5f,-0.5f,0.f},glm::vec2{0.f,1.f},glm::vec3{0.f,0.f,1.f}},//Bottom Left
		{glm::vec3{0.5f,-0.5f,0.f},glm::vec2{1.f,1.f} ,glm::vec3{0.f,0.f,1.f}},//Bottom Right
		{glm::vec3{0.5f,0.5f,0.f},glm::vec2{1.f,0.f}  ,glm::vec3{0.f,0.f,1.f}}, //Top Right
		{glm::vec3{-0.5f,0.5f,0.f},glm::vec2{0.f,0.f} ,glm::vec3{0.f,0.f,1.f}}//Top left
	};

	std::vector<unsigned int> indices =
	{
		0,1,2,0,2,3
	};
	GLenum type = GL_TRIANGLES;
	Model* model = new Model(name, MODEL_TYPE::PLANE, type, std::move(vertices), std::move(indices));

	assert(model != nullptr);

	AddModel(model);
}

void ModelManager::CubeInit()
{
	std::string name = "Cube";
	std::vector<Model::VertexAttribute> vertices =
	{
		// Front face
		{{-0.5f, -0.5f,  0.5f}, {0.f, 1.f}, {0.f, 0.f, 1.f}}, // 0
		{{ 0.5f, -0.5f,  0.5f}, {1.f, 1.f}, {0.f, 0.f, 1.f}}, // 1
		{{ 0.5f,  0.5f,  0.5f}, {1.f, 0.f}, {0.f, 0.f, 1.f}}, // 2
		{{-0.5f,  0.5f,  0.5f}, {0.f, 0.f}, {0.f, 0.f, 1.f}}, // 3

		// Back face
		{{ 0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {0.f, 0.f, -1.f}}, // 4
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, 0.f, -1.f}}, // 5
		{{-0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {0.f, 0.f, -1.f}}, // 6
		{{ 0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {0.f, 0.f, -1.f}}, // 7

		// Left face
		{{-0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {-1.f, 0.f, 0.f}}, // 8
		{{-0.5f, -0.5f,  0.5f}, {1.f, 1.f}, {-1.f, 0.f, 0.f}}, // 9
		{{-0.5f,  0.5f,  0.5f}, {1.f, 0.f}, {-1.f, 0.f, 0.f}}, // 10
		{{-0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {-1.f, 0.f, 0.f}}, // 11

		// Right face
		{{ 0.5f, -0.5f,  0.5f}, {0.f, 1.f}, {1.f, 0.f, 0.f}}, // 12
		{{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {1.f, 0.f, 0.f}}, // 13
		{{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {1.f, 0.f, 0.f}}, // 14
		{{ 0.5f,  0.5f,  0.5f}, {0.f, 0.f}, {1.f, 0.f, 0.f}}, // 15

		// Top face
		{{-0.5f,  0.5f,  0.5f}, {0.f, 1.f}, {0.f, 1.f, 0.f}}, // 16
		{{ 0.5f,  0.5f,  0.5f}, {1.f, 1.f}, {0.f, 1.f, 0.f}}, // 17
		{{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f}, {0.f, 1.f, 0.f}}, // 18
		{{-0.5f,  0.5f, -0.5f}, {0.f, 0.f}, {0.f, 1.f, 0.f}}, // 19

		// Bottom face
		{{-0.5f, -0.5f, -0.5f}, {0.f, 1.f}, {0.f, -1.f, 0.f}}, // 20
		{{ 0.5f, -0.5f, -0.5f}, {1.f, 1.f}, {0.f, -1.f, 0.f}}, // 21
		{{ 0.5f, -0.5f,  0.5f}, {1.f, 0.f}, {0.f, -1.f, 0.f}}, // 22
		{{-0.5f, -0.5f,  0.5f}, {0.f, 0.f}, {0.f, -1.f, 0.f}}, // 23
	};

	std::vector<unsigned int> indices =
	{
		// Front face
		0, 1, 2, 0, 2, 3,
		// Back face
		4, 5, 6, 4, 6, 7,
		// Left face
		8, 9,10, 8,10,11,
		// Right face
		12,13,14,12,14,15,
		// Top face
		16,17,18,16,18,19,
		// Bottom face
		20,21,22,20,22,23
	};

	GLenum type = GL_TRIANGLES;
	Model* model = new Model(name, MODEL_TYPE::CUBE, type, std::move(vertices), std::move(indices));

	assert(model != nullptr);

	AddModel(model);
}

#include <iostream>
void ModelManager::LoadModel(const std::string& _fileName)
{
	int model_name_end_pos = _fileName.find('/', 0);
	std::string model_name = _fileName.substr(0, model_name_end_pos);

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("../Extern/Assets/Model/tempShip/" + _fileName,
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cout << _fileName << " Model 로드 실패 : " << importer.GetErrorString() << std::endl;
		return;
	}
	LoadNode(scene->mRootNode, scene);
	//LoadMaterials(scene);
}

void ModelManager::RenderModel()
{
}

void ModelManager::ClearModel()
{
}

void ModelManager::LoadNode(aiNode* _node, const aiScene* _scene)
{
	for (size_t i = 0; i < _node->mNumMeshes; i++)
	{
		// node->mMeshes[i] : 메시 자체가 아니고, 메시의 ID를 의미한다.
		// 실제 메시는 scene에 저장되어있기 때문에 이렇게 참조하게 된다.
		LoadMesh(_scene->mMeshes[_node->mMeshes[i]], _scene);
	}

	// 자식 노드들을 재귀호출을 통해 순회하며 메시를 쭉 로드한다.
	for (size_t i = 0; i < _node->mNumChildren; i++)
	{
		LoadNode(_node->mChildren[i], _scene);
	}
}

// 실제로 VBO, IBO로 쏴줄 정보들을 구성한다.
void ModelManager::LoadMesh(aiMesh* _mesh, const aiScene* _scene)
{
	std::vector<Model::VertexAttribute> vertices;
	std::vector<unsigned int> indices;
	
	for (size_t i = 0; i < _mesh->mNumVertices; i++)
	{		
		// position				
		glm::vec3 pos;
		pos={ _mesh->mVertices[i].x,_mesh->mVertices[i].y,_mesh->mVertices[i].z };		

		// texture
		glm::vec2 texture;
		if (_mesh->mTextureCoords[0])
		{
			texture={ _mesh->mTextureCoords[0][i].x ,_mesh->mTextureCoords[0][i].y };
		}
		else // 존재하지 않을 경우 그냥 0을 넣어주기
		{
			texture={ 0.f,0.f };			
		}

		// normal (aiProcess_GenSmoothNormals를 적용했기 때문에 없을 수가 없다.)
		glm::vec3 normals;
		normals={ _mesh->mNormals[i].x ,_mesh->mNormals[i].y,_mesh->mNormals[i].z };

		Model::VertexAttribute mva;
		mva.position = pos;
		mva.texcoord = texture;
		mva.normals = normals;

		vertices.push_back(mva);
	}

	// indices 채워주기
	for (size_t i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//todo 이거 정리하셈
	std::string name = "tempShip";
	Model* model = new Model(name, std::move(vertices), std::move(indices));

	assert(model != nullptr);

	AddModel(model);
	// meshList에 mesh를 채워줌과 동시에, meshToTex에는 그 mesh의 materialIndex를 채워준다.
	// 이렇게 meshList와 meshToTex를 나란히 채워줌으로써 mesh와 맞는 material을 손쉽게 찾을 수 있다.
	m_vMaterials.push_back(_mesh->mMaterialIndex);
}

#include "TextureResource.h"
void ModelManager::LoadMaterials(const aiScene* _scene)
{
	std::string name = "tempShip";
	m_vTextureList.resize(_scene->mNumMaterials);
	for (size_t i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* material = _scene->mMaterials[i];

		m_vTextureList[i] = nullptr;

		// 텍스쳐가 존재하는 지 먼저 확인
		if (material->GetTextureCount(aiTextureType_BASE_COLOR))
		{
			aiString texturePath;
			// 텍스쳐 경로를 가져오는 데 성공했다면
			if (material->GetTexture(aiTextureType_BASE_COLOR, 0, &texturePath) == aiReturn_SUCCESS)
			{
				// 혹시나 텍스쳐 경로가 절대 경로로 되어있다면 그에 대한 처리
				int idx = std::string(texturePath.data).rfind("/");
				std::string textureName = std::string(texturePath.data).substr(idx + 1);

				std::string texPath = "Models/" + name + "/textures/" + textureName;

				m_vTextureList[i] = new TextureResource(texPath.c_str());

				// 텍스쳐를 디스크에서 메모리로 로드, GPU로 쏴준다.				
				m_vTextureList[i]->Load(texPath.c_str());
				//if ()
				//{ // 실패 시
				//	std::cout << "텍스쳐 로드 실패 : " << texPath << std::endl;
				//	delete m_vTextureList[i];
				//	m_vTextureList[i] = nullptr;
				//}
			}
		}

		// textureList에 텍스쳐를 담는데 실패했다면
		if (!m_vTextureList[i])
		{
			std::cout << "Load Texture failed" << std::endl;
		}
	}
}



