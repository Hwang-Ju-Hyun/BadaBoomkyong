#include "LightManager.h"
#include "ComponentManager.h"

LightManager::LightManager(){}

LightManager::~LightManager(){}


Light* LightManager::GetLight(const std::string& _name)
{
	auto iter = m_mapLight.find(_name);
	if (iter != m_mapLight.end())
		return iter->second;
}