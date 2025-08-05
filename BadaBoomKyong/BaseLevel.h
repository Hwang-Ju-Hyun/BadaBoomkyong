#pragma once
#include <string>
#include "header.h"
class BaseLevel
{
public:
	BaseLevel() = delete;
	BaseLevel(STAGE_TYPE _stageType,const std::string& _name);	
	virtual ~BaseLevel();
private:
	std::string m_sName="";
	STAGE_TYPE m_eStageType;
public:
	void SetName(const std::string& _name);
	inline const std::string& GetName()const { return m_sName; }
	inline STAGE_TYPE GetStageType()const { return m_eStageType; }
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};