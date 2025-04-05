#pragma once
#include <string>
class BaseLevel
{
public:
	BaseLevel() = delete;
	BaseLevel(const std::string& _name);
	virtual ~BaseLevel();
private:
	std::string m_sName="";
public:
	void SetName(const std::string& _name);
	inline const std::string& GetName()const { return m_sName; }
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};