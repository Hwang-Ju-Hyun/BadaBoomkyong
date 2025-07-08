#pragma once
#include "Singleton.h"
#include <vector>
#include "header.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model;
class TextureResource;

class ModelManager
{
public:
	SINGLETON(ModelManager);
//todo : temp�� ���߿� �����丵  �ϼ�
public:
	std::vector<Model*> m_vModels;
	std::vector<size_t> m_vMaterials;
	std::vector<TextureResource*> m_vTextureList;
public:
	inline void AddModel(Model* _model){ m_vModels.push_back(_model); }
	inline std::vector<Model*> GetAllModels() { return m_vModels; }
	Model* FindModel(const std::string& _modelName);
	Model* FindModel(MODEL_TYPE _modelType);
public:
	Model* m_pCustomModel = nullptr;
public:
	void Init();
	void Exit();
//2d
private:
	void LineInit();
	void TriangleInit();
	void CircleInit();
	void RectangleInit();
//3d
private:
	void PlaneInit();
	void CubeInit();

public:
	Model* LoadModel(const std::string& _fileName); // ���� �޸𸮿� �ø���.
	void RenderModel(); // �������Ѵ�.
	void ClearModel(); // �޸𸮿��� ������.	
private:
	// ���ȣ��Ǹ� ��带 ��ȸ�ϱ� ���� �Լ�
	void LoadNode(aiNode* _node, const aiScene* _scene);
	// ���� �޽� ������Ʈ�� �����Ͽ� ���ؽ� ������ �ε��Ѵ�.
	void LoadMesh(aiMesh* _mesh, const aiScene* _scene);
	// �ؽ��ĸ� �ε��Ѵ�.
	void LoadMaterials(const aiScene* _scene);
public:
	static int g_mesh_cnt;
};