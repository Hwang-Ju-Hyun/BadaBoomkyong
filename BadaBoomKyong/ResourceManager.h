#pragma once
#include "Singleton.h"
#include <map>
#include <string>
#include <vector>

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
		ttf,
		jpeg
	};
public:
	enum SELECT_EXTENSION GetExtension(const std::string& _extension)const;
public:
	BaseResource* GetAndLoad(const std::string& _resName, const std::string& _path);
	BaseResource* GetAndLoadCubeMap(const std::string& _resName, const std::vector<std::string>& _path);
	BaseResource* FindResource(const std::string& _resName,const std::string& _path);
	inline void AddResource(const std::string& _resName,const std::string& _path, BaseResource* _res) { m_mapResource.insert(std::make_pair(std::make_pair( _resName,_path),_res)); }
public:
	void RemoveAllRes();
};

