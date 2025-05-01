#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

class BaseRTTI
{
public:
	BaseRTTI();
	virtual ~BaseRTTI();
public:
	//todo : when work donoe should reset to be abstract
	virtual void LoadFromJson(const json& _str) =0;
	virtual json SaveToJson(const json& _str)=0;
};

