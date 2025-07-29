#pragma once
#include "Singleton.h"
#include <map>
#include <string>

class BaseResource;

class ResourceManager
{
public:
	SINGLETON(ResourceManager);
public:
	std::map<std::pair<std::string,std::string>, BaseResource*> m_mapResource;
private: 
	enum SELECT_EXTENSION
	{
		png,
		jpg,
		wav,
		mp3,
		ttf
	};
public:
	enum SELECT_EXTENSION GetExtension(const std::string& _extension)const;
public:
	BaseResource* GetAndLoad(const std::string& _resName, const std::string& _path);
	BaseResource* FindResource(const std::string& _resName,const std::string& _path);
	inline void AddResource(const std::string& _resName, BaseResource* _res) { m_mapResource.insert({ _resName,_res }); }
public:
	void RemoveAllRes();
};

