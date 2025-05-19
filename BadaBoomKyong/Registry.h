#pragma once
#include "Singleton.h"
#include <map>
#include <string>
#include <unordered_map>
#include "BaseFactory.h"

class BaseRTTI;
class IFactory;

class Registry
{
public:
	SINGLETON(Registry);
private:
	std::map<std::string, BaseRTTI*(*)()> m_mapRTTI;	
	std::unordered_map<std::string, IFactory*> m_hashFactoryRegistry;
public:
	BaseRTTI* FindOrCreate(const std::string& _type);

};