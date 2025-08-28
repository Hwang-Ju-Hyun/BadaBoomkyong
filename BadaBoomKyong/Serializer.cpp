#include "Serializer.h"
#include "header.h"
#include <fstream>
#include <iostream>
#include "GameObject.h"
#include "GameObjectManager.h"
#include "BaseComponent.h"
#include "Registry.h"
#include "BaseRTTI.h"
#include "FactoryManager.h"
#include "Model.h"
#include "ModelManager.h"

Serializer::Serializer() {}

Serializer::~Serializer(){}

GameObject* Serializer::LoadPrefab(const std::string& _path)
{	
	return LoadJson_Object(_path);
}

GameObject* Serializer::LoadJson_Object(const std::string& _path)
{
	std::fstream file;
	file.open(_path, std::fstream::in);
	ASSERT_MSG(file.is_open(), ("Can't open file : " + _path).c_str());

	json js_all_data;
	file >> js_all_data;
	file.close();	
	GameObject* obj = nullptr;
	for (auto& item : js_all_data)
	{		
		obj = CreateObjectFromJson(item);
	}

	return obj;
}

GameObject* Serializer::CreateObjectFromJson(json _item)
{
	json::iterator iter_name = _item.find(NameTypeInJson);
	json::iterator iter_model = _item.find(ModelTypeNameInJson);
	json::iterator iter_model_path= _item.find(ModelPathInJson);
	json::iterator iter_group = _item.find(GroupTypeNameInJson);

	ASSERT_MSG(iter_name!=_item.end(),"Name not exist");
	ASSERT_MSG(iter_name != _item.end(), "Model not exist");

	std::string obj_name = (*iter_name);
	MODEL_TYPE obj_model = (*iter_model);	
	GROUP_TYPE obj_group = (*iter_group);
	
	GameObject* obj = new GameObject(obj_name, obj_model,obj_group);	
	ASSERT_MSG(obj != nullptr, "GameObject can't construct");

	if (iter_model_path != _item.end())
	{
		auto model_mgr = ModelManager::GetInstance();
		Model* custom_model = model_mgr->LoadModel((*iter_model_path));
		obj->SetModel(custom_model);
	}
	
	json::iterator iter_comp = _item.find(ComponentNameInJson);
	
	auto components = *iter_comp;

	for (auto element : components)
	{
		json::iterator component_type = element.find(ComponentTypeNameInJson);
		
		if (component_type == element.end())
			continue;

		std::string type_name = *component_type;

		BaseRTTI* p = Registry::GetInstance()->FindOrCreate(type_name);

		if (p != nullptr)
			p->LoadFromJson(element);
	}
	return obj;
}


void Serializer::SaveJson_Object(const std::string& _path, bool _is3d)
{
	std::vector<GameObject*> all_objs = GameObjectManager::GetInstance()->GetAllObjects();
	json js_all_data;

	for (int i = 0;i < all_objs.size();i++)
	{
		if (all_objs[i]->GetIsSerializable())
		{
			json js_components;
			json js_obj;
			std::string obj_name = all_objs[i]->GetName();
			size_t obj_id = all_objs[i]->GetID();
			js_obj[NameTypeInJson] = obj_name;
			js_obj[IDTypeInJson] = obj_id;
			if (all_objs[i]->GetIs3D() == _is3d)
			{
				js_obj[DimensionTypeNameInJson] = all_objs[i]->GetIs3D();
				for (auto element : all_objs[i]->GetAllComponentsOfObj_vec())
				{
					BaseComponent* comp = element;
					js_components.push_back(comp->SaveToJson(_path));
				}
				js_obj[ComponentNameInJson] = js_components;
				js_obj[ModelTypeNameInJson] = all_objs[i]->GetModelType();
				if (all_objs[i]->GetModelType() == MODEL_TYPE::CUSTOM_MODEL)
				{
					js_obj[ModelPathInJson] = all_objs[i]->GetModel()->GetPath();
				}
				js_obj[GroupTypeNameInJson] = all_objs[i]->GetGroupType();
				js_all_data.push_back(js_obj);
			}
		}		
	}
	std::fstream file;
	file.open(_path, std::fstream::out);
	if (!file.is_open())
	{
		return ;
	}

	file << std::setw(2) << js_all_data;
	file.close();
}