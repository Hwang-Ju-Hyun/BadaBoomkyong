#pragma once
#include "Singleton.h"
#include <string>
#include "json.hpp"

class GameObject;

using json = nlohmann::ordered_json;

class Serializer
{
public:
	SINGLETON(Serializer);
public:
	GameObject* LoadJson(const std::string& _path);
	void SaveJson(const std::string& _path);
	GameObject* CreateObjectFromJson(json _item);
private:
	const char* ModelTypeNameInJson = "Model";
	const char* ComponentNameInJson = "Components";
	const char* NameTypeInJson = "Name";
	const char* ComponentTypeNameInJson = "Type";
};

