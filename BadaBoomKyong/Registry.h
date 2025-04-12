#pragma once
#include "Singleton.h"
#include <map>
#include <string>

class BaseRTTI;

class Registry
{
public:
	SINGLETON(Registry);
private:
	std::map<std::string, BaseRTTI*(*)()> m_mapRTTI;
public:
	BaseRTTI* FindOrCreate(const std::string& _type);
};