#include "ModelManager.h"
#include "Model.h"
#include <cassert>
#include <utility>
#include "Mesh.h"

int ModelManager::g_mesh_cnt = 0;

ModelManager::ModelManager()
{	
}

ModelManager::~ModelManager()
{	
	
}

Model* ModelManager::FindModel(const std::string& _modelName)
{
	auto models = GetAllModels();	
	for (auto mdl : models)
	{
		if (mdl->GetName() == _modelName)
			return mdl;
	}
	return nullptr;
}

Model* ModelManager::FindModel(MODEL_TYPE _modelType)
{
	if (_modelType != MODEL_TYPE::CUSTOM_MODEL)
	{
		auto models = GetAllModels();
		for (auto mdl : models)
		{
			if (mdl->GetModelType() == _modelType)
				return mdl;
		}
		return nullptr;
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
}

void ModelManager::Exit()
{	
	size_t size = m_vModels.size();
	for (int i = 0;i < size;i++)
	{		
		if (m_vModels[i])
		{
			delete m_vModels[i];
			m_vModels[i] = nullptr;
		}		
	}
	m_vModels.clear();
	std::vector<Model*> temp;
	temp.swap(m_vModels);
}

void ModelManager::LineInit()
{
	std::string name = "Line";
	std::vector<Mesh::VertexAttribute> vertices =
	{
		{glm::vec3{ -0.5f, 0.f, 0.f }, glm::vec2{ 0.f, 0.f }},
		{glm::vec3{ 0.5f, 0.f, 0.f }, glm::vec2{ 0.f, 0.f }}
	};	

	GLenum type = GL_LINES;
	Mesh* mesh = new Mesh(MODEL_TYPE::LINE, type, std::move(vertices));
	assert(mesh != nullptr);

	Model* model = new Model(name, MODEL_TYPE::LINE);

	assert(model != nullptr);
	model->AddMesh(mesh);
}

void ModelManager::TriangleInit()
{
	std::string name = "Triangle";	
	std::vector<Mesh::VertexAttribute> vertices =						
	{								
		{glm::vec3{ -0.5f, -0.5f, 0.f }, glm::vec2{ 0.f, 0.f }}, // Bottom Left
		{glm::vec3{  0.0f,  0.5f, 0.f }, glm::vec2{ 0.5f, 1.f }}, // Top Center
		{glm::vec3{  0.5f, -0.5f, 0.f }, glm::vec2{ 1.f, 0.f }}  // Bottom Right
	};							
	GLenum type = GL_TRIANGLES;
	Mesh* mesh = new Mesh(MODEL_TYPE::TRIANGLE, type, std::move(vertices));
	assert(mesh != nullptr);

	Model* model = new Model(name, MODEL_TYPE::TRIANGLE);

	assert(model != nullptr);
	model->AddMesh(mesh);
}

void ModelManager::RectangleInit()
{	
	std::string name = "Rectangle";
	std::vector<Mesh::VertexAttribute> vertices =
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
	Mesh* mesh = new Mesh(MODEL_TYPE::RECTANGLE, type, std::move(vertices), std::move(indices));
	assert(mesh != nullptr);

	Model* model = new Model(name, MODEL_TYPE::RECTANGLE);

	assert(model != nullptr);
	model->AddMesh(mesh);
}

void ModelManager::CircleInit()
{
	//todo
}

void ModelManager::PlaneInit()
{
	std::string name = "Plane";
	std::vector<Mesh::VertexAttribute> vertices =
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
	Mesh* mesh = new Mesh(MODEL_TYPE::PLANE, type, std::move(vertices), std::move(indices));
	assert(mesh != nullptr);
	
	Model* model = new Model(name, MODEL_TYPE::PLANE);

	assert(model != nullptr);
	model->AddMesh(mesh);
}

void ModelManager::CubeInit()
{
	std::string name = "Cube";
	std::vector<Mesh::VertexAttribute> vertices =
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
	Mesh* mesh = new Mesh(MODEL_TYPE::CUBE,type, std::move(vertices), std::move(indices));	
	assert(mesh != nullptr);
	
	Model* model=new Model(name,MODEL_TYPE::CUBE);
	
	assert(model != nullptr);
	model->AddMesh(mesh);	
}

#include <iostream>
Model* ModelManager::LoadModel(const std::string& _filePath)
{	
	int str_find_cnt = 0;
	for (int i = _filePath.size() - 1;i >= 0;i--)
	{
		if (_filePath[i] == '.')
		{			
			break;
		}
		str_find_cnt++;
	}	
	std::string model_name = "Nothing";
	int str_iter = 0;
	char find_slash = ' ';
	while (1)
	{		
		if (find_slash == '/')
		{
			str_iter--;
			model_name=_filePath.substr(_filePath.size() - str_iter,str_iter- str_find_cnt -1);
			break;
		}					
		find_slash = _filePath[_filePath.size()-1 - str_iter];
		str_iter++;
	}	

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_filePath,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace | // (Normal mapping ��� �� �ʿ�)
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_SortByPType |
		aiProcess_PreTransformVertices // glTF���� node transform ���� �� ����
	);

	m_pCustomModel = new Model(model_name, MODEL_TYPE::CUSTOM_MODEL, _filePath);

	if (!scene)
	{
		std::cout << _filePath << " Fail Load Model  : " << importer.GetErrorString() << std::endl;
		return nullptr;
	}

	LoadNode(scene->mRootNode, scene);	

	LoadMaterials(scene, _filePath);
	
	ModelManager::GetInstance()->AddModel(m_pCustomModel);
	return m_pCustomModel;
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

#include "Material.h"
// ������ VBO, IBO�� ���� �������� �����Ѵ�.
void ModelManager::LoadMesh(aiMesh* _mesh, const aiScene* _scene)
{
	std::vector<Mesh::VertexAttribute> vertices;
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
		if (_mesh->HasNormals())
			normals = { _mesh->mNormals[i].x ,_mesh->mNormals[i].y,_mesh->mNormals[i].z };		

		Mesh::VertexAttribute mva;
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
	GLenum type = GL_TRIANGLES;	
	std::string name = m_pCustomModel->GetName() + std::to_string(g_mesh_cnt++);
	Mesh* mesh = new Mesh(MODEL_TYPE::CUSTOM_MODEL, type,std::move(vertices), std::move(indices));
	//Material* material = new Material;	
	//mesh->SetMaterial(material);

	assert(mesh != nullptr);
	 	
	m_pCustomModel->AddMesh(mesh);
	m_pCustomModel->m_meshCnt = g_mesh_cnt;

	// meshList�� mesh�� ä���ܰ� ���ÿ�, meshToTex���� �� mesh�� materialIndex�� ä���ش�.
	// �̷��� meshList�� meshToTex�� ������ ä�������ν� mesh�� �´� material�� �ս��� ã�� �� �ִ�.
	m_vMaterials.push_back(_mesh->mMaterialIndex);
}

#include "TextureResource.h"
#include "ResourceManager.h"
void ModelManager::LoadMaterials(const aiScene* _scene,const std::string& _filePath)
{			
	const std::string name = m_pCustomModel->GetName();
	m_vTextureList.resize(_scene->mNumMaterials);
	Material* mat = nullptr;
	
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
				//todo : ��� �����̸� �ʹ� �ߺ��Ǵ°� ���� �����丵 �� �� �̰� �� ��ġ��
				std::string pathStr = texturePath.C_Str();								
				int idx = pathStr.find_last_of("/");
				std::string textureName = (idx != std::string::npos) ? pathStr.substr(idx + 1) : pathStr;				
				int file_path_idx = _filePath.find_last_of("/");

				std::string texture_path = (file_path_idx != std::string::npos) ? _filePath.substr(0, file_path_idx + 1) : _filePath;
				std::string texPath = texture_path + textureName;
				
				Material* mat = new Material;

				if (i < m_pCustomModel->GetMeshes().size()) {
					m_pCustomModel->GetMeshes()[i]->SetMaterial(mat);
				}
				//m_pCustomModel->GetMeshes()[i]->SetMaterial(mat);
				TextureResource* texture = new TextureResource(texPath);
				ResourceManager::GetInstance()->AddResource(textureName,texPath,texture);
				mat->SetTexture(texture);

				BaseResource* tex = ResourceManager::GetInstance()->GetAndLoad(textureName, texPath);
				TextureResource* texture_res = dynamic_cast<TextureResource*>(tex);
				texture_res->Load(texPath);
				//m_vTextureList[i] = new TextureResource(texPath);
				//m_vTextureList[i]->Load(texPath.c_str());
			}		
		}		
		// textureList�� �ؽ��ĸ� ��µ� �����ߴٸ�
		if (!m_vTextureList[i])
		{
			std::cout << "Load Texture failed" << std::endl;
		}
	}
}