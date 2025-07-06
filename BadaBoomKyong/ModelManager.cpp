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
	//todo : load �̰� �̻���
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
		std::cout << _fileName << " Model �ε� ���� : " << importer.GetErrorString() << std::endl;
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
		// node->mMeshes[i] : �޽� ��ü�� �ƴϰ�, �޽��� ID�� �ǹ��Ѵ�.
		// ���� �޽ô� scene�� ����Ǿ��ֱ� ������ �̷��� �����ϰ� �ȴ�.
		LoadMesh(_scene->mMeshes[_node->mMeshes[i]], _scene);
	}

	// �ڽ� ������ ���ȣ���� ���� ��ȸ�ϸ� �޽ø� �� �ε��Ѵ�.
	for (size_t i = 0; i < _node->mNumChildren; i++)
	{
		LoadNode(_node->mChildren[i], _scene);
	}
}

// ������ VBO, IBO�� ���� �������� �����Ѵ�.
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
		else // �������� ���� ��� �׳� 0�� �־��ֱ�
		{
			texture={ 0.f,0.f };			
		}

		// normal (aiProcess_GenSmoothNormals�� �����߱� ������ ���� ���� ����.)
		glm::vec3 normals;
		normals={ _mesh->mNormals[i].x ,_mesh->mNormals[i].y,_mesh->mNormals[i].z };

		Model::VertexAttribute mva;
		mva.position = pos;
		mva.texcoord = texture;
		mva.normals = normals;

		vertices.push_back(mva);
	}

	// indices ä���ֱ�
	for (size_t i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//todo �̰� �����ϼ�
	std::string name = "tempShip";
	Model* model = new Model(name, std::move(vertices), std::move(indices));

	assert(model != nullptr);

	AddModel(model);
	// meshList�� mesh�� ä���ܰ� ���ÿ�, meshToTex���� �� mesh�� materialIndex�� ä���ش�.
	// �̷��� meshList�� meshToTex�� ������ ä�������ν� mesh�� �´� material�� �ս��� ã�� �� �ִ�.
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

		// �ؽ��İ� �����ϴ� �� ���� Ȯ��
		if (material->GetTextureCount(aiTextureType_BASE_COLOR))
		{
			aiString texturePath;
			// �ؽ��� ��θ� �������� �� �����ߴٸ�
			if (material->GetTexture(aiTextureType_BASE_COLOR, 0, &texturePath) == aiReturn_SUCCESS)
			{
				// Ȥ�ó� �ؽ��� ��ΰ� ���� ��η� �Ǿ��ִٸ� �׿� ���� ó��
				int idx = std::string(texturePath.data).rfind("/");
				std::string textureName = std::string(texturePath.data).substr(idx + 1);

				std::string texPath = "Models/" + name + "/textures/" + textureName;

				m_vTextureList[i] = new TextureResource(texPath.c_str());

				// �ؽ��ĸ� ��ũ���� �޸𸮷� �ε�, GPU�� ���ش�.				
				m_vTextureList[i]->Load(texPath.c_str());
				//if ()
				//{ // ���� ��
				//	std::cout << "�ؽ��� �ε� ���� : " << texPath << std::endl;
				//	delete m_vTextureList[i];
				//	m_vTextureList[i] = nullptr;
				//}
			}
		}

		// textureList�� �ؽ��ĸ� ��µ� �����ߴٸ�
		if (!m_vTextureList[i])
		{
			std::cout << "Load Texture failed" << std::endl;
		}
	}
}



