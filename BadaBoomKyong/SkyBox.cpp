#include "SkyBox.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "CubeMapResource.h"
#include "ResourceManager.h"
#include <vector>
#include "Serializer.h"


SkyBox::SkyBox(GameObject* _owner)
	:BaseComponent(_owner)
{
	SetName("SkyBox");
}

SkyBox::~SkyBox()
{
}

BaseRTTI* SkyBox::CreateSkyBoxComponent()
{
	GameObject* last_obj = GameObjectManager::GetInstance()->GetLastObject();
	BaseRTTI* comp = last_obj->AddComponent_and_Get(SkyBoxTypeName, new SkyBox(last_obj));
	if (comp != nullptr)
		return comp;
	return nullptr;
}

void SkyBox::LoadFromJson(const json& _str)
{
	auto comp_data = _str.find(CompDataName);
	if (comp_data != _str.end())
	{
		auto cubemap_name = comp_data->find(SkyBoxName);	
		auto pathFaces_list = comp_data->find(SkyBoxFacesPathName);
		if (pathFaces_list != comp_data->end() && pathFaces_list->is_array())
		{
			std::vector<std::string> faces;
			for (const auto& stateValue : *pathFaces_list)
			{				
				faces.push_back(stateValue.get<std::string>());				
			}			
			m_pCubeMapResource = dynamic_cast<CubeMapResource*>(ResourceManager::GetInstance()->GetAndLoadCubeMap(cubemap_name.value(),faces));
		}
	}
}

json SkyBox::SaveToJson(const json& _str)
{
	json data;
	auto serial = Serializer::GetInstance();
	data[serial->ComponentTypeNameInJson] = SkyBoxTypeName;

	json compData;
	compData[SkyBoxName] = { m_pCubeMapResource->GetResourceName()};

	int i = 0;
	const std::vector<std::string>* faces = m_pCubeMapResource->GetFacesCubeMap();
	for (auto iter =faces->begin();iter != faces->end();iter++)
	{
		compData[SkyBoxFacesPathName][i] = (std::string)*iter;
		i++;
	}
	compData[SkyBoxFacesPathName] = m_pCubeMapResource->GetResourcePath();

	data[CompDataName] = compData;
	return data;
}
