#pragma once
#include "Singleton.h"
#include <string>
#include "json.hpp"

class GameObject;

class Serializer
{
public:
	SINGLETON(Serializer);
public:
	GameObject* LoadJson(const std::string& _path);
	GameObject* CreateObjectFromJson(json _item);
};

