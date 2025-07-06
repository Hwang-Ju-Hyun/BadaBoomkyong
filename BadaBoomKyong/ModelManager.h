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
//todo : temp임 나중에 리펙토링 하셈
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
	void LoadModel(const std::string& _fileName); // 모델을 메모리에 올린다.
	void RenderModel(); // 렌더링한다.
	void ClearModel(); // 메모리에서 내린다.	
private:
	// 재귀호출되며 노드를 순회하기 위한 함수
	void LoadNode(aiNode* _node, const aiScene* _scene);
	// 실제 메시 오브젝트를 참조하여 버텍스 정보를 로드한다.
	void LoadMesh(aiMesh* _mesh, const aiScene* _scene);
	// 텍스쳐를 로드한다.
	void LoadMaterials(const aiScene* _scene);
};