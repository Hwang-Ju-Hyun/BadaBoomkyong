#include "ModelManager.h"
#include "Model.h"
#include <cassert>
#include <utility>

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
	SkyBoxInit();
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
	
	CaculateTangent(vertices,indices);


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

	CaculateTangent(vertices, indices);

	GLenum type = GL_TRIANGLES;
	Mesh* mesh = new Mesh(MODEL_TYPE::CUBE,type, std::move(vertices), std::move(indices));	
	assert(mesh != nullptr);
	
	Model* model=new Model(name,MODEL_TYPE::CUBE);
	
	assert(model != nullptr);
	model->AddMesh(mesh);	
}

void ModelManager::SkyBoxInit()
{
	std::string name = "SkyBox";
	std::vector<Mesh::VertexAttribute> vertices =
	{
		// Back face
		{{-1.0f,  1.0f, -1.0f}, {}, {}},
		{{-1.0f, -1.0f, -1.0f}, {}, {}},
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},
		{{ 1.0f,  1.0f, -1.0f}, {}, {}},
		{{-1.0f,  1.0f, -1.0f}, {}, {}},

		// Left face
		{{-1.0f, -1.0f,  1.0f}, {}, {}},
		{{-1.0f, -1.0f, -1.0f}, {}, {}},
		{{-1.0f,  1.0f, -1.0f}, {}, {}},
		{{-1.0f,  1.0f, -1.0f}, {}, {}},
		{{-1.0f,  1.0f,  1.0f}, {}, {}},
		{{-1.0f, -1.0f,  1.0f}, {}, {}},

		// Right face
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},
		{{ 1.0f, -1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f, -1.0f}, {}, {}},
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},

		// Front face
		{{-1.0f, -1.0f,  1.0f}, {}, {}},
		{{-1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f, -1.0f,  1.0f}, {}, {}},
		{{-1.0f, -1.0f,  1.0f}, {}, {}},

		// Top face
		{{-1.0f,  1.0f, -1.0f}, {}, {}},
		{{ 1.0f,  1.0f, -1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{ 1.0f,  1.0f,  1.0f}, {}, {}},
		{{-1.0f,  1.0f,  1.0f}, {}, {}},
		{{-1.0f,  1.0f, -1.0f}, {}, {}},

		// Bottom face
		{{-1.0f, -1.0f, -1.0f}, {}, {}},
		{{-1.0f, -1.0f,  1.0f}, {}, {}},
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},
		{{ 1.0f, -1.0f, -1.0f}, {}, {}},
		{{-1.0f, -1.0f,  1.0f}, {}, {}},
		{{ 1.0f, -1.0f,  1.0f}, {}, {}}
	};

	// 인덱스 필요 없음
	std::vector<unsigned int> indices;
	
	GLenum type = GL_TRIANGLES;
	Mesh* mesh = new Mesh(MODEL_TYPE::SKY_BOX, type, std::move(vertices), std::move(indices));
	assert(mesh != nullptr);

	Model* model = new Model(name, MODEL_TYPE::SKY_BOX);

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
		aiProcess_FlipUVs |
		aiProcess_JoinIdenticalVertices|
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace | // (Normal mapping 사용 시 필요)
		aiProcess_ImproveCacheLocality |
		aiProcess_RemoveRedundantMaterials |
		aiProcess_SortByPType 		|
		aiProcess_GenSmoothNormals
	);

	if (!scene || !scene->HasMeshes())
	{
		std::cout << "Assimp failed to load file: " << importer.GetErrorString() << std::endl;
		return nullptr;
	}
	
	for (size_t i = 0; i < scene->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[i];
		if (!mesh->HasNormals()) {
			std::cout << "Mesh " << i << " has no normals!" << std::endl;
		}
	}

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

void ModelManager::LoadNode(aiNode* node, const aiScene* scene, const aiMatrix4x4& parentTransform)
{
	// 현재 노드 변환행렬과 부모행렬 곱하기
	aiMatrix4x4 globalTransform = parentTransform * node->mTransformation;

	// 이 노드가 가진 모든 메시 처리
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		unsigned int meshIndex = node->mMeshes[i];
		aiMesh* mesh = scene->mMeshes[meshIndex];
		LoadMesh(mesh, scene, globalTransform);
	}

	// 자식 노드 재귀 처리
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		LoadNode(node->mChildren[i], scene, globalTransform);
	}
}

#include "Material.h"
// 실제로 VBO, IBO로 쏴줄 정보들을 구성한다.
void ModelManager::LoadMesh(aiMesh* _mesh, const aiScene* _scene, const aiMatrix4x4& transform)
{
	std::vector<Mesh::VertexAttribute> vertices;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < _mesh->mNumVertices; i++)
    {
        // aiVector3D에 변환 적용
        aiVector3D aiPos = _mesh->mVertices[i];
        aiPos *= transform; // aiMatrix4x4 곱셈

        glm::vec3 pos(aiPos.x, aiPos.y, aiPos.z);

        glm::vec2 texcoord{0.f, 0.f};
        if (_mesh->mTextureCoords[0])
            texcoord = { _mesh->mTextureCoords[0][i].x, _mesh->mTextureCoords[0][i].y };

        glm::vec3 normals{0.f, 0.f, 0.f};
        if (_mesh->HasNormals())
        {
            aiVector3D aiNormal = _mesh->mNormals[i];
            aiNormal *= transform; // 노말도 transform 적용
            normals = { aiNormal.x, aiNormal.y, aiNormal.z };
        }

		glm::vec3 tangents{ 0.f,0.f,0.f };
		if (_mesh->HasTangentsAndBitangents())
		{
			aiVector3D aiTangents = _mesh->mTangents[i];
			tangents = { aiTangents.x,aiTangents.y,aiTangents.z };
		}

        Mesh::VertexAttribute vertex;
        vertex.position = pos;
        vertex.texcoord = texcoord;
        vertex.normals = normals;
		vertex.tangent = tangents;


        vertices.push_back(vertex);
    }

    // 인덱스 채우기
    for (size_t i = 0; i < _mesh->mNumFaces; i++)
    {
        aiFace face = _mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


	/*if (_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = _scene->mMaterials[_mesh->mMaterialIndex];
		LoadMaterials(material, myMesh);
	}*/

	//todo 이거 정리하셈
	GLenum type = GL_TRIANGLES;	
	std::string name = m_pCustomModel->GetName() + std::to_string(g_mesh_cnt++);
	Mesh* mesh = new Mesh(MODEL_TYPE::CUSTOM_MODEL, type,std::move(vertices), std::move(indices));
	//Material* material = new Material;	
	//mesh->SetMaterial(material);

	assert(mesh != nullptr);
	 	
	m_pCustomModel->AddMesh(mesh);
	m_pCustomModel->m_meshCnt = g_mesh_cnt;

	// meshList에 mesh를 채워줌과 동시에, meshToTex에는 그 mesh의 materialIndex를 채워준다.
	// 이렇게 meshList와 meshToTex를 나란히 채워줌으로써 mesh와 맞는 material을 손쉽게 찾을 수 있다.
	m_vMaterials.push_back(_mesh->mMaterialIndex);
}

#include "TextureResource.h"
#include "ResourceManager.h"
void ModelManager::LoadMaterials(const aiScene* _scene,const std::string& _filePath)
{			
	const std::string name = m_pCustomModel->GetName();

	// 모델이 가진 모든 Mesh 순회
	for (size_t i = 0; i < _scene->mNumMeshes; i++)
	{
		aiMesh* mesh = _scene->mMeshes[i];
		int matIndex = mesh->mMaterialIndex; // 이 Mesh가 참조하는 Material Index

		if (matIndex < 0 || matIndex >= (int)_scene->mNumMaterials)
			continue;

		aiMaterial* material = _scene->mMaterials[matIndex];
		Material* mat = new Material;

		aiTextureType typesToCheck[] = {
		aiTextureType_DIFFUSE,
		aiTextureType_BASE_COLOR,
		aiTextureType_AMBIENT,  // 일부 FBX는 ambient에 들어감
		aiTextureType_NORMALS,
		aiTextureType_UNKNOWN   // FBX 임베디드 텍스처가 여기로 오는 경우도 있음
		};
		if (_scene->HasTextures()) {
			for (unsigned int i = 0; i < _scene->mNumTextures; i++) {
				aiTexture* tex = _scene->mTextures[i];
				std::cout << "Embedded texture: " << tex->mWidth << "x" << tex->mHeight << std::endl;
			}
		}
		for (auto type : typesToCheck) {
			if (material->GetTextureCount(type) > 0) {
				aiString texturePath;				
				if (material->GetTexture(type, 0, &texturePath) == aiReturn_SUCCESS)
				{
					std::string pathStr = texturePath.C_Str();
					std::cout << "Found texture at type=" << type << " : " << pathStr << std::endl;
					
					int idx = pathStr.find_last_of("/\\"); // 윈도우/리눅스 경로 둘 다 고려
					std::string textureName = (idx != std::string::npos) ? pathStr.substr(idx + 1) : pathStr;

					int file_path_idx = _filePath.find_last_of("/\\");
					std::string texture_path = (file_path_idx != std::string::npos) ? _filePath.substr(0, file_path_idx + 1) : _filePath;
					std::string texPath = texture_path + textureName;

					// ResourceManager 통해서 로드 & 캐싱
					if (type == aiTextureType_DIFFUSE || type == aiTextureType_BASE_COLOR)
					{
						BaseResource* tex = ResourceManager::GetInstance()->GetAndLoad(textureName, texPath);
						TextureResource* texture_res = dynamic_cast<TextureResource*>(tex);
						if (texture_res)
						{
							mat->SetTexture(texture_res);
						}
					}
					else if (type == aiTextureType_NORMALS)
					{
						BaseResource* tex = ResourceManager::GetInstance()->GetAndLoad(textureName, texPath);
						TextureResource* texture_res = dynamic_cast<TextureResource*>(tex);
						if (texture_res)
						{
							mat->SetNormalMap(texture_res);
						}
					}
					
				}
			}
		}		

		// ─────────────────────────────
		// Mesh에 Material 연결
		// ─────────────────────────────
		if (i < m_pCustomModel->GetMeshes().size())
		{
			m_pCustomModel->GetMeshes()[i]->SetMaterial(mat);
		}
	}
}

void ModelManager::CaculateTangent(std::vector<Mesh::VertexAttribute>& _vertices, std::vector<unsigned int> _indices)
{	
	for (auto& v : _vertices)	
		v.tangent = glm::vec3({ 0.f,0.f,0.f });		
	
	for (size_t i = 0; i < _indices.size(); i += 3)// 인덱스 3개씩 끊어서 삼각형 단위 처리
	{
		unsigned int i0 = _indices[i];
		unsigned int i1 = _indices[i + 1];
		unsigned int i2 = _indices[i + 2];

		Mesh::VertexAttribute& v0 = _vertices[i0];
		Mesh::VertexAttribute& v1 = _vertices[i1];
		Mesh::VertexAttribute& v2 = _vertices[i2];
		glm::vec3 edge1 = v1.position - v0.position;
		glm::vec3 edge2 = v2.position - v0.position;

		glm::vec2 deltaUV1 = v1.texcoord - v0.texcoord;		
		glm::vec2 deltaUV2 = v2.texcoord - v0.texcoord;

		float r = deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y;
		if (std::fabs(r) <=g_epsilon)	
			r = 1.0f;		
		else		
			r = 1.0f / r;		

		glm::vec3 tangent = (edge1 * deltaUV2.y - edge2 * deltaUV1.y) * r;		
		
		v0.tangent += tangent;
		v1.tangent += tangent;
		v2.tangent += tangent;		
	}	
	for (auto& v : _vertices)	
		v.tangent = glm::normalize(v.tangent);	

}