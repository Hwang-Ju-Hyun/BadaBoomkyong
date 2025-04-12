#include "Serializer.h"
#include "header.h"
#include <fstream>
#include <iostream>

using json = nlohmann::ordered_json;

Serializer::Serializer() {}

Serializer::~Serializer(){}

GameObject* Serializer::LoadJson(const std::string& _path)
{
	std::fstream file;	
	ASSERT_MSG(file.is_open(),"Can't open file : %s",_path);
	
	json js_all_data;
	file >> js_all_data;
	file.close();
		
	for (auto& item : js_all_data)
	{
		CreateObjectFromJson(item);
	}

	return nullptr;
}

GameObject* Serializer::CreateObjectFromJson(json _item)
{
	
}
