#include "BaseLevel.h"

BaseLevel::BaseLevel(STAGE_TYPE _stageType, const std::string& _name)
	:m_eStageType(_stageType)
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