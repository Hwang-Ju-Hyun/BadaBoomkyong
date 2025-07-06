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
private:
	std::vector<Model*> m_vModels;
//todo : temp�� ���߿� �����丵 �ϼ�
	std::vector<size_t> m_vMaterials;
	std::vector<TextureResource*> m_vTextureList;
public:
	inline void AddModel(Model* _model){ m_vModels.push_back(_model); }
	inline std::vector<Model*> GetAllModels() { return m_vModels; }
	Model* FindModel(MODEL_TYPE _modelType);
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

private:
	void LoadModel(const std::string& _fileName); // ���� �޸𸮿� �ø���.
	void RenderModel(); // �������Ѵ�.
	void ClearModel(); // �޸𸮿��� ������.	
private:
	// ���ȣ��Ǹ� ��带 ��ȸ�ϱ� ���� �Լ�
	void LoadNode(aiNode* _node, const aiScene* _scene);
	// ���� �޽� ������Ʈ�� �����Ͽ� ���ؽ� ������ �ε��Ѵ�.
	void LoadMesh(aiMesh* _mesh, const aiScene* _scene);
	// �ؽ��ĸ� �ε��Ѵ�.
	void LoadMaterials(const aiScene* _scene);
};