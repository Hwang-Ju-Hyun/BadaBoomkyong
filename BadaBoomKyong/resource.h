#pragma once
#include <string>
#include <vector>

class BaseResource
{
public:
	BaseResource() = delete;
	BaseResource(const std::string& _name);
	virtual ~BaseResource();
private:
	std::string m_sResourceName;
	std::string m_sResourcePath;
protected:
	unsigned char* m_cData = nullptr;
public:
	unsigned char* GetData()const { return m_cData; }
public:
	inline void SetResourceName(const std::string& _resName)	{ m_sResourceName = _resName; }
	inline const std::string& GetResourceName()const			{ return m_sResourceName; }
	inline void SetResourcePath(const std::string& _resPath)	{ m_sResourcePath = _resPath; }
	inline const std::string& GetResourcePath()const			{ return m_sResourcePath; }
public:
	virtual void Load(const std::string& _path) = 0;
	virtual void LoadCubeMap(const std::vector<std::string>& _faces) {}
	virtual void UnLoad() = 0;
};