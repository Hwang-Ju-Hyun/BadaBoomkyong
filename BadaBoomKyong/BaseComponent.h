#pragma once
#include <string>
class BaseComponent
{
private:
	std::string m_sName;
public:
	inline void SetName(const std::string _name) { m_sName = _name; }
	inline const std::string& GetName()const { return m_sName; }
};