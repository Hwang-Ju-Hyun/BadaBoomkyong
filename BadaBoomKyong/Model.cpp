#include "Mesh.h"
#include "Model.h"
#include "ModelManager.h"

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
	for (int i = 0;i < m_vMeshes.size();i++)
	{		
		delete m_vMeshes[i];
		m_vMeshes[i] = nullptr;
	}
	/*m_vMeshes.clear();
	std::vector<Mesh*> temp = m_vMeshes;
	temp.swap(m_vMeshes);*/
} 

void Model::Draw()
{	
	for (int i = 0;i < m_vMeshes.size();i++)
	{
		m_vMeshes[i]->Draw();
	}
}
