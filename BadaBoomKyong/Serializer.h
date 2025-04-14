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
public:
	static constexpr const char* ModelTypeNameInJson = "Model";
	static constexpr const char* ComponentNameInJson = "Components";
	static constexpr const char* NameTypeInJson = "Name";
	static constexpr const char* ComponentTypeNameInJson = "Type";
};

