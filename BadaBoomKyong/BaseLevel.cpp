#include "BaseLevel.h"

BaseLevel::BaseLevel(const std::string& _name) 
{
	SetName(_name);
}

BaseLevel::~BaseLevel() 
{

}

void BaseLevel::SetName(const std::string& _name) 
{
	m_sName = _name;
}