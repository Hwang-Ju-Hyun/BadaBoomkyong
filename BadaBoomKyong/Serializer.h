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
	GameObject* LoadJson_Object(const std::string& _path);
	void SaveJson_Object(const std::string& _path,bool _is3d);
	GameObject* CreateObjectFromJson(json _item);
public:
	static constexpr const char* ModelTypeNameInJson = "Model";
	static constexpr const char* ComponentNameInJson = "Components";
	static constexpr const char* NameTypeInJson = "Name";
	static constexpr const char* IDTypeInJson = "ID";
	static constexpr const char* ComponentTypeNameInJson = "Type";
	static constexpr const char* GroupTypeNameInJson = "Group";
	static constexpr const char* DimensionTypeNameInJson = "Is3D";
};

