#pragma once
#include "BaseLevel.h"
class Stage03 :
    public BaseLevel
{	
public:
	Stage03(const std::string& _name);
	virtual ~Stage03() override;
public:
	virtual void Init()	override;
	virtual void Update()override;
	virtual void Exit()	override;
};

