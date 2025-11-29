#include "ResourceManager.h"
#include "CubeMapResource.h"
#include "TextureResource.h"
#include <cassert>

ResourceManager::ResourceManager(){}
ResourceManager::~ResourceManager(){}

ResourceManager::SELECT_EXTENSION ResourceManager::GetExtension(const std::string& _extension) const
{
	if (_extension == "png")
	{
		return SELECT_EXTENSION::png;
	}
	else if (_extension == "jpg")
	{
		return SELECT_EXTENSION::jpg;
	}
	else if (_extension == "jpeg")
	{
		return SELECT_EXTENSION::jpeg;
	}
	else if (_extension == "wav")
	{
		return SELECT_EXTENSION::wav;
	}
	else if (_extension == "mp3")
	{
		return SELECT_EXTENSION::mp3;
	}
	else if (_extension == "ttf")
	{
		return SELECT_EXTENSION::ttf;
	}	
}

BaseResource* ResourceManager::GetAndLoad(const std::string& _resName,const std::string& _path)
{
	auto iter = m_mapResource.find({ _resName,_path });
	if (iter == m_mapResource.end())
	{
		std::string ext = _path.substr(_path.find_last_of(".") + 1);
		SELECT_EXTENSION extension = GetExtension(ext);
		BaseResource* resource = nullptr;						
		switch (extension)
		{
		case ResourceManager::png:
			resource = new TextureResource(_resName);
			resource = dynamic_cast<BaseResource*>(resource);
			assert(resource != nullptr);
			m_mapResource.insert(std::make_pair(std::make_pair(_resName, _path), resource));					
			break;
		case ResourceManager::jpg:
			resource = new TextureResource(_resName); 
			resource = dynamic_cast<BaseResource*>(resource);
			assert(resource != nullptr);
			m_mapResource.insert(std::make_pair(std::make_pair(_resName,_path), resource));
			break;
		case ResourceManager::wav:
			break;
		case ResourceManager::mp3:
			break;
		case ResourceManager::ttf:
			break;
		case ResourceManager::jpeg:
			resource = new TextureResource(_resName);
			resource = dynamic_cast<BaseResource*>(resource);
			assert(resource != nullptr);
			m_mapResource.insert(std::make_pair(std::make_pair(_resName, _path), resource));
			break;
		default:
			break;
		}
		resource->Load(_path);
		return resource;
	}
	else
		return iter->second;
}

BaseResource* ResourceManager::GetAndLoadCubeMap(const std::string& _resName, const std::vector<std::string>& _path)
{
	auto iter = m_mapResource.find({ _resName,_path[0] });
	if (iter == m_mapResource.end())
	{
		BaseResource* resource = nullptr;
		resource = new CubeMapResource(_resName);
		resource->LoadCubeMap(_path);
		assert(resource != nullptr);
		m_mapResource.insert(std::make_pair(std::make_pair(_resName, _path[0]), resource));
		return resource;
	} 
	return iter->second;
}

BaseResource* ResourceManager::FindResource(const std::string& _resName, const std::string& _path)
{
	auto iter = m_mapResource.find({ _resName,_path });
	if (iter != m_mapResource.end())
		return iter->second;
    return nullptr;
}

void ResourceManager::RemoveAllRes()
{
	for (auto iter = m_mapResource.begin(); iter != m_mapResource.end();)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
			iter->second = nullptr;
			iter = m_mapResource.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
}
