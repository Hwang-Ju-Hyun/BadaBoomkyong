#include "Mesh.h"
#include "Model.h"
#include "ModelManager.h"

//Model::Model(const std::string& _name, MODEL_TYPE _modelType, GLenum _primitiveType, std::vector<VertexAttribute>&& _vertices, std::vector<unsigned int>&& _indices)
//	:m_sName(_name),
//	m_eModelType(_modelType),
//	m_ePrimitiveType(_primitiveType),
//	m_vVertices(_vertices),
//	m_vIndices(_indices)
//{
//	/*m_vIndices.size() <= 2 ? m_bEBO = false : m_bEBO = true;
//	UploadBuffers();*/
//}
//
//Model::Model(const std::string& _name,std::vector<VertexAttribute>&& _vertices, std::vector<unsigned int>&& _indices)
//	:m_sName(_name),
//	m_vVertices(_vertices),
//	m_vIndices(_indices)
//{
//	/*m_vIndices.size() <= 2 ? m_bEBO = false : m_bEBO = true;
//	UploadBuffers();*/
//}

Model::Model(const std::string _name, MODEL_TYPE _modelType, const std::string& _path)
	:m_sName(_name),
	m_eModelType(_modelType),
	m_sPath(_path)
{
	if (_modelType == MODEL_TYPE::CUSTOM_MODEL && _path == "Nothing")	
		assert(false);
	//디폴트 모델이라면
	if (_modelType != MODEL_TYPE::CUSTOM_MODEL)
	{
		m_meshCnt = 1;
		ModelManager::GetInstance()->AddModel(this);
	}
	
}

Model::~Model()
{	
	//mesh들 지워주셈
	for (int i = 0;i < m_vMeshes.size();i++);
} 

void Model::Draw()
{
	for (int i = 0;i < m_vMeshes.size();i++)
	{
		m_vMeshes[i]->Draw();
	}
}
